library(tidyverse)
library(magrittr) 
library(lubridate)
library(scales)
library(wordcloud)
library(plotly)
library(skimr)
library(janitor)
library(tidytext)
library(sentimentr)
library(widyr)
library(igraph)
library(ggraph)
library(formattable)
library(stopwords)

bing_lexicon <- get_sentiments('bing')


reddit_vm <- read_csv("reddit_vm.csv") %>% 
  clean_names()
reddit_vm <- reddit_vm %>% 
   mutate(across(where(is.character), tolower)) %>% 
  mutate(date = as_date(timestamp)) %>%
  clean_names()

glimpse(reddit_vm)

reddit_vm %>% skim() %>%
  filter(n_missing != 0) %>%
  as_tibble() %>%
  select(skim_variable, n_missing, complete_rate) %>%
  mutate(missing_rate = round(abs(complete_rate - 1) * 100, 1)) %>%
  ggplot(aes(
    x = fct_reorder(skim_variable, n_missing),
    y = missing_rate,
    fill = skim_variable,
    label = paste0(missing_rate, "%")
  )) +
  geom_col() +
  geom_text(
    size = 4.5,
    hjust = 1.5,
    vjust = 0.25,
    col = "white"
  ) +
  coord_flip() +
  theme(legend.position = "none") +
  scale_y_continuous(label = label_percent(scale = 1)) +
  scale_fill_manual(values = c("#e41a1c",
                               "#984ea3")) +
  labs(
    title = "Missing Data rate using skimr package",
    subtitle = "Plot, Missing Data distribution",
    caption = "Data source: Kaggle.com, Reddit Vaccine Myths",
    x = "Variable name",
    y = "Count"
  )

  reddit_vm %>%
  select(date) %>%
  mutate(year = year(date)) %>%
  count(year, sort = TRUE) %>%
  ggplot(aes(x = year,
             y = n,
             label = n)) +
  geom_line(show.legend = FALSE,
            col = "blue",
            size = 2) +
  geom_label(
    vjust = -0.5,
    size = 4,
    col = "black",
    label.size = 1
  ) +
  scale_fill_viridis(discrete = TRUE, option = "E") +
  scale_y_continuous(expand = expansion(add = c(15, 100))) +
  theme(axis.text.x = element_text(angle = 90)) +
  theme(strip.background = element_rect(fill = "black")) +
  theme(strip.text = element_text(colour = 'white')) +
  labs(
    title = "Number of Posts/year",
    x = "Year"
  )

set.seed(1967)
reddit_vm_text <- reddit_vm %>% select(body, id, score)
StopWords <- get_stopwords(source = "smart")

reddit_vm_text <- reddit_vm_text %>% 
  unnest_tokens(output = word, input = body) %>%
  anti_join(StopWords, by = "word") %>%
  filter(str_detect(word, "[:alpha:]"),
         word == gsub('\\b\\w{1,2}\\b','',word),
         word == gsub(pattern = "\\www\\w*", "", word),
         !word %in% c("http", "https")
  )
words_connections_plot <- function(reddit_vm_text,
                                   min_word_count = 25,
                                   min_correlation = 0.3) { 
  id_words <- reddit_vm_text %>%
    select(word) %>%
    count(word, name = "word_count") %>%
    filter(word_count >= min_word_count)
  
  word_correlations <- reddit_vm_text %>%
    select(-score) %>%
    semi_join(id_words, by = "word") %>%
    pairwise_cor(item = word, feature = id) %>%
    filter(correlation >= min_correlation)
  
  graph_from_data_frame(d = word_correlations,
                        vertices = id_words %>%
                          semi_join(word_correlations, by = c("word" = "item1"))) %>%
    ggraph(layout = "fr") +
    geom_edge_link(aes(edge_color = correlation), edge_width = 1.4 ) +
    geom_node_point(size = 3.6) +
    geom_node_text(aes(color = word_count, label = name), repel = TRUE) +
    labs(col = "Word \nCount") +
    theme_void()
  
}
set.seed(1967)

reddit_vm_text %>%
  words_connections_plot(min_word_count = 50, min_correlation = 0.35) +
  theme(panel.border = element_rect(
    colour = "black",
    fill = NA,
    size = 1
  )) +
  scale_colour_gradient(low = "gray", high = "#a65628") +
  scale_edge_color_continuous(low = "blue", high = "red") +
  labs(
    title = "Correlation Plot",
    caption = "Data source: Kaggle.com, Reddit Vaccine Myths"
  )

reddit_vm_senti_body <- reddit_vm %>% select(body, date, score, id)


reddit_vm_senti_body %>%
  unnest_tokens(output = word, input = body) %>%
  anti_join(StopWords, by = "word") %>%
  inner_join(bing_lexicon, by = "word") %>%
  mutate(date = year(date)) %>%
  group_by(id,date, sentiment) %>%
  summarise(Count = n()) %>%
  pivot_wider(names_from = sentiment,
              values_from = Count,
              values_fill = 0) %>% 
  mutate(sentiment = positive - negative) %>% 
  ggplot(aes(x = id,
             y = sentiment)) +
  geom_col(aes(fill = ifelse(sentiment > 0,"red", "blue")), show.legend = FALSE) +
  facet_grid(vars(date), scales = "free_x") +
  theme(axis.text.x = element_text(angle = 90, size = 2)) +
  theme(legend.position = "none") +
  labs(fill = "Year") +
  labs(
    title = "Sentiment/Year",
    caption = "Data source: Kaggle.com, Reddit Vaccine Myths",
    x = "Year",
    y = "Sentiment"
  )
nrc_lexicon <- get_sentiments('nrc')
reddit_vm_senti_body %>%
  unnest_tokens(output = word, input = body) %>%
  anti_join(StopWords, by = "word") %>%
  inner_join(nrc_lexicon, by = "word") %>%
  count(sentiment, word, sort = TRUE) %>%
  pivot_wider(names_from = sentiment,
              values_from = n,
              values_fill = 0) %>%
  column_to_rownames(var = "word") %>%
  comparison.cloud(
    colors = c(
      "#a6cee3",
      "#1f78b4",
      "#b2df8a",
      "#33a02c",
      "#fb9a99",
      "#e31a1c",
      "#fdbf6f",
      "#ff7f00",
      "#cab2d6"
    ),
    max.words = 500,
    title.size = 1.5,
    title.colors = c(
      "#a6cee3",
      "#1f78b4",
      "#b2df8a",
      "#33a02c",
      "#fb9a99",
      "#e31a1c",
      "#fdbf6f",
      "#ff7f00",
      "#cab2d6"
    )
  )
frequency_dataframe = reddit_vm_text %>% count(word) %>% arrange(desc(n))

