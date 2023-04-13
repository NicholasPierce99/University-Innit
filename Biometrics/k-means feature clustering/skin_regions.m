clc;
close all;
clear;
X = imread('Lihua.jpg');
K = 3;

%shape the image to be the same size as the centroid matrix
imdata = reshape(X, [], 3);
imdata = double(imdata);

%C random number generation, randomly sample K
%pixels from the image
C = random(X);

%returns nn - final centroid values, idx - pixel centroid clustering results
[IDX, nn] = kmeans(imdata, K, 'dist', 'sqEuclidean', 'start', C);
reclassify_idx = reclassify(IDX, nn, K);
%Using 3 clusters to make it easier for users to not have click a thousand
%times, block out all non skin pixels from the output and display image
for i = 1: size(reclassify_idx)
    if reclassify_idx(i) ~= 3
        reclassify_idx(i) = 0;
    end
end
reclassify_idx = reshape(reclassify_idx, [283, 383]);
imagesc(reclassify_idx);

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
%selects 3 random pixels in image X
function [C] = random(X)
    [h, w, K] = size(X);
    
    c1 = impixel(X);
    c2 = impixel(X);
    c3 = impixel(X);
    C = [c1; c2; c3];
end

