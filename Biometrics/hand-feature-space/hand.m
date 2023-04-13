V = imread('hand1.png');
V = rgb2gray(V);
W = imread('hand2.png');
W = rgb2gray(W);
X = imread('hand3.png');
X = rgb2gray(X);
Y = imread('hand4.png');
Y = rgb2gray(Y);
Z = imread('hand5.png');
Z = rgb2gray(Z);

distances = zeros([14, 1]);

for i =1: 15
    distances(i) = sample(Y);
end

function[eucl_dist] = sample(img)
    imshow(img);
    [x, y, c] = improfile();
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
    for i = 1:size(c) - 1
        if (c(i) > 100) && (c(i + 1) < 100)
            x1 = x(i + 1);
            y1 = y(i + 1);
        elseif (c(i) < 100) && (c(i + 1) > 100)
            x2 = x(i);
            y2 = y(i);
        end
    end
    pair_1 = [x1, y1];
    disp(pair_1);
    pair_2 = [x2, y2];
    disp(pair_2);
    eucl_dist = norm(pair_1 - pair_2);
end