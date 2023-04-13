clc;
close all;
clear;
X = imread('Lihua.jpg');
K = input('select a K');

%shape the image to be the same size as the centroid matrix
imdata = reshape(X, [], 3);
imdata = double(imdata);

%sample accomplishes task of random number generation, randomly sample K
%pixels from the image
%returns nn - final centroid values, idx - pixel centroid clustering results
result = [];
for i = 1: 25
    [IDX, nn] = kmeans(imdata, K, 'dist', 'sqEuclidean', 'start', 'sample');
    reclassify_idx = reclassify(IDX, nn, K);
    reclassify_idx = reshape(reclassify_idx, [283, 383]);
    %result is an hxwxiterations matrix of pixel assignments
    result(:, :, i) = reclassify_idx;
end
%result is an hxwxiterations array
%iterate through and calculate mode of all centroid placements 
% in h,w, i = 1:25
for h = 1: 283
    for w = 1: 383
        c = mode(result(h,w, :));
        s = ['pixel', num2str(h), ',', num2str(w), 'is most likely at cluster', num2str(c)];
        disp(s);
    end
end

%reclassifies pixels by ordering the columns
function [idx] = reclassify(idx, centroids, K)
    sorted_centroids = sortrows(centroids);
    for i = 1: K
        if centroids(i, 1) ~= sorted_centroids(i, 1)
            [row, column] = find(centroids == sorted_centroids(i, 1));
            for j = 1: size(idx)
                if idx(j) == row
                    idx(j) = i;
                end
            end
        end
    end
    
end
%{
function [C] = random(K, X)
    C = zeros(K, 3);
    [h, w, K] = size(X);
    rand_x = randperm(w, K);
    rand_y = randperm(h, K);
    
    for i = 1: K
        C(i,:) = impixel(X, rand_x(i), rand_y(i));
    end
end
%}
