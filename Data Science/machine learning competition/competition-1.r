library(tidyverse)
library(glmnet)

train = read_csv("train.csv")
test = read_csv("test.csv")
y = train$pstr
x = test$pstr
Y = test[,3:84]
X = train[,3:84]

X$pstr = NULL
Y$pstr = NULL

X$SEX = as.numeric(as.factor(X$SEX))
Y$SEX = as.numeric(as.factor(Y$SEX))

pstr_table_train = train %>% group_by(higheduc) %>% summarise(train_mnpstr = mean(pstr))
pstr_table_test = test %>% group_by(higheduc) %>% summarise(test_mnpstr = mean(pstr))

X_join = left_join(X, pstr_table_train, by = "higheduc")
Y_join = left_join(Y, pstr_table_test, by = "higheduc")

X_join$higheduc = NULL
Y_join$higheduc = NULL

X_join[is.na(X_join)] = 0
Y_join[is.na(Y_join)] = 0
Y_join = as.matrix(Y_join)
X_join = as.matrix(X_join)

train_sparse = sparse.model.matrix(~., Y_join)
test_sparse = sparse.model.matrix(~., X_join)

library(tidyverse)
library(glmnet)
library(keras)
library(tensorflow)
library(dplyr)
library(gbm)         
library(xgboost)
library(Metrics)

train = read_csv("train.csv")
test = read_csv("test.csv")
test_id = seq(from = 1, to = 8352, by = 1)
test$SEX = as.numeric(as.factor(test$SEX))
test$higheduc = as.numeric(as.factor(test$higheduc))
drops <- c("ID","interview_date")
test[ , !(names(test) %in% drops)]
test$pstr = NULL

test[is.na(test)] = 0

y = train$pstr
y = as.numeric(y)
X = train[,3:84]
X$pstr = NULL
X$SEX = as.numeric(as.factor(X$SEX))

pstr_table = train %>% group_by(higheduc) %>% summarise(mnpstr = mean(pstr))

X_join = left_join(X, pstr_table, by = "higheduc")
X_join$higheduc = NULL

X_join$hincome[is.na(X_join$hincome)] = mean(X_join$hincome, na.rm = T)
X_join$fam_size_cv[is.na(X_join$fam_size_cv)] = mean(X_join$hincome, na.rm = T)
X_join$fam_actions_cv___10[is.na(X_join$fam_actions_cv___10)] = mean(X_join$fam_actions_cv___10, na.rm = T)
X_join$child_social_media_time_cv[is.na(X_join$child_social_media_time_cv)] = mean(X_join$child_social_media_time_cv, na.rm = T)
X_join$physical_activities_hr_cv[is.na(X_join$physical_activities_hr_cv)] = mean(X_join$physical_activities_hr_cv, na.rm = T)
X_join$sitting_weekday_hour_cv[is.na(X_join$sitting_weekday_hour_cv)] = mean(X_join$sitting_weekday_hour_cv, na.rm = T)


final_df = X_join %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv")
final_df = as.matrix(final_df)
final_df = xgb.DMatrix(data = final_df, label = y)


test = test %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv")
test$hincome[is.na(test$hincome)] = mean(test$hincome, na.rm = T)
test$fam_size_cv[is.na(test$fam_size_cv)] = mean(test$hincome, na.rm = T)
test$fam_actions_cv___10[is.na(test$fam_actions_cv___10)] = mean(test$fam_actions_cv___10, na.rm = T)
test$child_social_media_time_cv[is.na(test$child_social_media_time_cv)] = mean(test$child_social_media_time_cv, na.rm = T)
test$physical_activities_hr_cv[is.na(test$physical_activities_hr_cv)] = mean(test$physical_activities_hr_cv, na.rm = T)
test$sitting_weekday_hour_cv[is.na(test$sitting_weekday_hour_cv)] = mean(test$sitting_weekday_hour_cv, na.rm = T)

test = as.matrix(test)
test = xgb.DMatrix(data = test)
xgbc = xgboost(data = final_df,min_child_weight=1, max.depth = 2, nrounds = 100)

pstr = predict(xgbc, test)
rmse = function(actual, predicted) {
  sqrt(mean((actual - predicted) ^ 2))
}

output <- data.frame(test_id, pstr)
summary(pstr)
write.csv(output,"C:\\Users\\Nick\\Desktop\\comp_res.csv", row.names = FALSE)

test$hincome[is.na(test$hincome)] = mean(test$hincome, na.rm = T)
test$fam_size_cv[is.na(test$fam_size_cv)] = mean(test$hincome, na.rm = T)
test$fam_actions_cv___10[is.na(test$fam_actions_cv___10)] = mean(test$fam_actions_cv___10, na.rm = T)
test$child_social_media_time_cv[is.na(test$child_social_media_time_cv)] = mean(test$child_social_media_time_cv, na.rm = T)
test$physical_activities_hr_cv[is.na(test$physical_activities_hr_cv)] = mean(test$physical_activities_hr_cv, na.rm = T)
test$sitting_weekday_hour_cv[is.na(test$sitting_weekday_hour_cv)] = mean(test$sitting_weekday_hour_cv, na.rm = T)

X_join$hincome[is.na(X_join$hincome)] = mode(X_join$hincome, na.rm = T)
X_join$fam_size_cv[is.na(X_join$fam_size_cv)] = mode(X_join$hincome, na.rm = T)
X_join$fam_actions_cv___10[is.na(X_join$fam_actions_cv___10)] = mode(X_join$fam_actions_cv___10, na.rm = T)
X_join$child_social_media_time_cv[is.na(X_join$child_social_media_time_cv)] = mode(X_join$child_social_media_time_cv, na.rm = T)
X_join$physical_activities_hr_cv[is.na(X_join$physical_activities_hr_cv)] = mode(X_join$physical_activities_hr_cv, na.rm = T)
X_join$sitting_weekday_hour_cv[is.na(X_join$sitting_weekday_hour_cv)] = mode(X_join$sitting_weekday_hour_cv, na.rm = T)

library(tidyverse)
library(glmnet)
library(keras)
library(tensorflow)
library(dplyr)
library(gbm)         
library(xgboost)
library(Metrics)
library(gdata)
train = read_csv("train.csv")
test = read_csv("test.csv")
test_id = seq(from = 1, to = 8352, by = 1)

test['pstr'] <- NA
join_df = join_df[,3:84]
join_df$SEX = as.numeric(as.factor(join_df$SEX))
join_df$higheduc = as.numeric(as.factor(join_df$higheduc))
join_df$pstr[is.na(join_df$pstr)] = mean(join_df$pstr, na.rm = T)
rmse_compare = join_df$pstr
print(join_df$pstr)
pstr_table = join_df %>% group_by(higheduc) %>% summarise(mnpstr = mean(pstr))

X_join = left_join(join_df, pstr_table, by = "higheduc")
X_join$higheduc = NULL

X_join$hincome[is.na(X_join$hincome)] = mean(X_join$hincome, na.rm = T)
X_join$fam_size_cv[is.na(X_join$fam_size_cv)] = mean(X_join$hincome, na.rm = T)
X_join$fam_actions_cv___10[is.na(X_join$fam_actions_cv___10)] = mean(X_join$fam_actions_cv___10, na.rm = T)
X_join$child_social_media_time_cv[is.na(X_join$child_social_media_time_cv)] = mean(X_join$child_social_media_time_cv, na.rm = T)
X_join$physical_activities_hr_cv[is.na(X_join$physical_activities_hr_cv)] = mean(X_join$physical_activities_hr_cv, na.rm = T)
X_join$sitting_weekday_hour_cv[is.na(X_join$sitting_weekday_hour_cv)] = mean(X_join$sitting_weekday_hour_cv, na.rm = T)

final_df = X_join %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv", "pstr")

set.seed(101)
train<-sample_n(final_df, 8522, replace = TRUE)
sid<-as.numeric(rownames(train))
test<-final_df[-sid,]
test_target = test$pstr
test = test %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv")
test = as.matrix(test)
test = xgb.DMatrix(data = test, label = test_target)
train_target = train$pstr
train = train %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv")
train = as.matrix(train)
train = xgb.DMatrix(data = train, label = train_target)

xgbc = xgboost(data = train, min_child_weight=1, max.depth = 2, nrounds = 100)

predictions = predict(xgbc, test)
res = rmse(test_target, predictions)
print(res)
output <- data.frame(test_id, predictions)
write.csv(output,"C:\\Users\\Nick\\Desktop\\comp_res.csv", row.names = FALSE)

model <- keras_model_sequential()
model %>%
model <- keras_model_sequential()
model %>%
  layer_dense(units = 256, activation = 'relu', input_shape = ncol(final_df)) %>% 
  layer_dropout(rate = .4) %>%
  layer_dense(units = 128, activation = 'relu') %>%
  layer_dense(units = 64, activation = 'relu') %>%
  layer_dropout(rate = .3) %>%
  layer_dense(units = 32, activation = 'relu') %>%
  layer_dropout(rate = .1) %>%
  layer_dense(units = 16, activation = 'relu') %>%
  layer_dense(units = 1, activation = 'linear')

model %>% compile(
  loss = 'MeanSquaredError',
  optimizer = optimizer_adam(),
  metrics = c('MeanSquaredError')
)

history <- model %>% fit(
  final_df, y,
  epochs = 200, batch_size = 256,
  validation_split = .2
)

model %>% compile(
  loss = 'MeanSquaredError',
  optimizer = optimizer_adam(),
  metrics = c('MeanSquaredError')
)

history <- model %>% fit(
  final_df, y,
  epochs = 200, batch_size = 128,
  validation_split = .2
)

output$pstr = predict(model, test)
write.csv(output,"C:\\Users\\Nick\\Desktop\\submission_results.csv", row.names = FALSE)

pstr = predict(model, test)
output <- data.frame(test_id, pstr)
write.csv(output,"C:\\Users\\Nick\\Desktop\\comp_res.csv", row.names = FALSE)

library(tidyverse)
library(glmnet)
library(keras)
library(tensorflow)
library(dplyr)
library(gbm)         
library(xgboost)
library(Metrics)
library(e1071)

train = read_csv("train.csv")
test = read_csv("test.csv")
test_id = seq(from = 1, to = 8352, by = 1)
test$SEX = as.numeric(as.factor(test$SEX))

X = train[,3:84]
X$SEX = as.numeric(as.factor(X$SEX))

pstr_table = train %>% group_by(higheduc) %>% summarise(mnpstr = mean(pstr))
X_join = left_join(X, pstr_table, by = "higheduc")
X_join$higheduc = NULL

X_join$hincome[is.na(X_join$hincome)] = mean(X_join$hincome, na.rm = T)
X_join$fam_size_cv[is.na(X_join$fam_size_cv)] = mean(X_join$hincome, na.rm = T)
X_join$fam_actions_cv___10[is.na(X_join$fam_actions_cv___10)] = mean(X_join$fam_actions_cv___10, na.rm = T)
X_join$child_social_media_time_cv[is.na(X_join$child_social_media_time_cv)] = mean(X_join$child_social_media_time_cv, na.rm = T)
X_join$physical_activities_hr_cv[is.na(X_join$physical_activities_hr_cv)] = mean(X_join$physical_activities_hr_cv, na.rm = T)
X_join$sitting_weekday_hour_cv[is.na(X_join$sitting_weekday_hour_cv)] = mean(X_join$sitting_weekday_hour_cv, na.rm = T)
X_join = X_join %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv", "mnpstr", "pstr")
set.seed(101) 
train_sample = sample_frac(X_join, 0.7, replace = TRUE)
sid = as.numeric(rownames(train_sample))
y = train_sample$pstr
test_sample = X_join[-sid,]
y1 = test_sample$pstr
train_sample = train_sample %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv", "mnpstr")
train_sample = as.matrix(train_sample)

test_sample = test_sample %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv", "mnpstr")
test_sample = as.matrix(test_sample)
test["mnpstr"] = 0
test %>% left_join(test, pstr_table, by = "higheduc")
view(test)

X_join$hincome[is.na(X_join$hincome)] = mode(X_join$hincome, na.rm = T)
X_join$fam_size_cv[is.na(X_join$fam_size_cv)] = mode(X_join$hincome, na.rm = T)
X_join$fam_actions_cv___10[is.na(X_join$fam_actions_cv___10)] = mode(X_join$fam_actions_cv___10, na.rm = T)
X_join$child_social_media_time_cv[is.na(X_join$child_social_media_time_cv)] = mode(X_join$child_social_media_time_cv, na.rm = T)
X_join$physical_activities_hr_cv[is.na(X_join$physical_activities_hr_cv)] = mode(X_join$physical_activities_hr_cv, na.rm = T)
X_join$sitting_weekday_hour_cv[is.na(X_join$sitting_weekday_hour_cv)] = mode(X_join$sitting_weekday_hour_cv, na.rm = T)
X_join = X_join %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv", "mnpstr", "pstr")

X_join$hincome[is.na(X_join$hincome)] = median(X_join$hincome, na.rm = T)
X_join$fam_size_cv[is.na(X_join$fam_size_cv)] = median(X_join$hincome, na.rm = T)
X_join$fam_actions_cv___10[is.na(X_join$fam_actions_cv___10)] = median(X_join$fam_actions_cv___10, na.rm = T)
X_join$child_social_media_time_cv[is.na(X_join$child_social_media_time_cv)] = median(X_join$child_social_media_time_cv, na.rm = T)
X_join$physical_activities_hr_cv[is.na(X_join$physical_activities_hr_cv)] = median(X_join$physical_activities_hr_cv, na.rm = T)
X_join$sitting_weekday_hour_cv[is.na(X_join$sitting_weekday_hour_cv)] = median(X_join$sitting_weekday_hour_cv, na.rm = T)
X_join = X_join %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv", "mnpstr", "pstr")

library(tidyverse)
library(glmnet)
library(keras)
library(tensorflow)
library(dplyr)
library(gbm)         
library(xgboost)
library(Metrics)
library(e1071)
library(randomForest)

train = read_csv("train.csv")
test = read_csv("test.csv")
test_id = seq(from = 1, to = 8352, by = 1)
test$SEX = as.numeric(as.factor(test$SEX))

X = train[,3:84]
X$SEX = as.numeric(as.factor(X$SEX))

pstr_table = train %>% group_by(higheduc) %>% summarise(mnpstr = mean(pstr))
X_join = left_join(X, pstr_table, by = "higheduc")
X_join$higheduc = NULL
forest_factor = as.numeric(X_join$pstr)
X_join = X_join %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv", "mnpstr", "pstr")
imputed_vals_train <- tibble::as_tibble(
  randomForest::rfImpute(forest_factor ~., ntree = 200, iter = 5, data = X_join) %>% select(SEX, hincome, fam_size_cv, fam_actions_cv___10, child_social_media_time_cv, physical_activities_hr_cv, sitting_weekday_hour_cv, pstr)
)
y = imputed_vals_train$pstr
imputed_vals_train$pstr = NULL
test = test %>% select("SEX", "hincome", "fam_size_cv", "fam_actions_cv___10", "child_social_media_time_cv", "physical_activities_hr_cv", "sitting_weekday_hour_cv")
test$hincome[is.na(test$hincome)] = mean(test$hincome, na.rm = T)
test$fam_size_cv[is.na(test$fam_size_cv)] = mean(test$hincome, na.rm = T)
test$fam_actions_cv___10[is.na(test$fam_actions_cv___10)] = mean(test$fam_actions_cv___10, na.rm = T)
test$child_social_media_time_cv[is.na(test$child_social_media_time_cv)] = mean(test$child_social_media_time_cv, na.rm = T)
test$physical_activities_hr_cv[is.na(test$physical_activities_hr_cv)] = mean(test$physical_activities_hr_cv, na.rm = T)
test$sitting_weekday_hour_cv[is.na(test$sitting_weekday_hour_cv)] = mean(test$sitting_weekday_hour_cv, na.rm = T)
test = as.matrix(test)
#test = xgb.DMatrix(data = test)
imputed_vals_train = as.matrix(imputed_vals_train)

#imputed_vals_train = xgb.DMatrix(data = imputed_vals_train, label = y)
#xgbc = xgboost(data = imputed_vals_train, min_child_weight = 1, max.depth = 2, nrounds = 200)

rf = randomForest(formula = y ~., data = imputed_vals_train, ntree = 100, mtry = 2)
pstr = predict(rf, test)
view(pstr)
output <- data.frame(test_id, pstr)
view(output)
write.csv(output,"C:\\Users\\Nick\\Desktop\\comp_res_.csv", row.names = FALSE)

