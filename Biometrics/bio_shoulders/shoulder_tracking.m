videoReader = VideoReader('biovid.mp4');
videoPlayer = vision.VideoPlayer('Position',[500, 500, 680, 520]);
writerObj = VideoWriter('biovid.mp4');
counter = 0;
open(writerObj);
while hasFrame(videoReader)
    X = readFrame(videoReader);
    Y = readFrame(videoReader);
    counter = counter + 1;
    % for each frame:
    %figure, imshow(X)
    I1 = rgb2gray(X);
    I1 = double(I1)/255;
    I1 = imresize(I1, .7);
    I1 = smoothn(I1,[11,11], 'gaussian', 1);

    % edges:
    E1 = double(edge(I1, 'canny'));

    %viola-jones:
    faceDetector = vision.CascadeObjectDetector();
    BB = step(faceDetector, I1);
    [rows, cols] = size(BB);
    for i = 1:rows
        for j = 1: cols
            if(BB(i, j) > 504)
                BB(i, j) = 100;
            end
        end
    end
    
    if(BB(1) + BB(3) > 504)
        BB(1) = BB(1) / 2;
        BB(3) = BB(3) / 2;
    end
    
    FACE = I1(BB(2):BB(2)+BB(4), BB(1):BB(1)+BB(3));
  
    % visualize:
    SF = insertShape(I1, 'Rectangle', BB);

    %LEFT SIDE
    Lbox = [ round(BB(1)-(BB(3)/2)), round(BB(2)+BB(4)/2), round(BB(3)/2), BB(4)];
    for i =1: size(Lbox)
        if(Lbox(i) <= 0)
            Lbox(i) = 1;
        end
    end
    Lsd = I1(Lbox(2):Lbox(2)+Lbox(4),Lbox(1):Lbox(1)+Lbox(3));
    %visualize:
    SLbox = insertShape(I1, 'Rectangle', Lbox);

    %LIKE THIS:
    P1 = [];
    for col = 1:size(Lsd,2)-5 %to average 5 columns and stay in bound
        %use average column value per row (sliding window)
        avg = [];
        for dr = 1:size(Lsd,1)
            v = mean(Lsd(dr,col:col+5)); % average 5 columns
            avg = [avg; v];
        end
        pks = fpeak([1:size(Lsd,1)],avg); %see link
        % test with plots
        % figure, plot(Lsd(:,col)),hold on,
        % plot(pks(:,1),pks(:,2),'r*')
        g = gradient(pks(:,2));
        [m,idx]=min(g); %depends on contrast: dark foreground vs bright background
        if(idx - 1 == 0)
           idx = 2;
        end
        P1 = [P1; [Lbox(2) + pks(idx-1,1),Lbox(1)+col]];
    end
    % FIT LINE (polynomial n=1)
    p = polyfit(P1(:,2),P1(:,1),1);
    x = [min(P1(:,2)):max(P1(:,2))]; % from one end to the other
    rowval = polyval(p,x);

    %USING EDGES:

    %edges left side only (preserve dimenstions to avoid coordinate
    %transformation)
    LE = zeros(size(I1));
    LE(Lbox(2):Lbox(2)+Lbox(4),Lbox(1):Lbox(1)+Lbox(3)) = E1(Lbox(2):Lbox(2)+Lbox(4),Lbox(1):Lbox(1)+Lbox(3));

    %Hough Transform:
    % https://www.mathworks.com/help/images/ref/hough.html
    % https://www.mathworks.com/help/images/ref/houghlines.html
    [H,theta,rho] = hough(LE);
    P=houghpeaks(H,5, 'threshold',ceil(0.3*max(H(:))));
    lines = houghlines(LE,theta,rho,P,'FillGap',20,'MinLength',10);
    figure, imshow(LE), imshow(I1), hold on
    plot(P1(:,2),P1(:,1),'c.'),plot(x,rowval,'r');
    
    max_len = 0;
    for k = 1:length(lines)
        xy = [lines(k).point1; lines(k).point2];
        plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');

        %Plot beginnings and ends of lines
        %plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow');
        %plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red');

        %Determine the endpoints of the longest line segment
        len = norm(lines(k).point1 - lines(k).point2);
        if (len>max_len)
            max_len = len;
            xy_long = xy;
        end
    end
    open(writerObj);
    frame = getframe(gcf);
    writeVideo(writerObj, frame);
    close(gcf);
end
close(writerObj);