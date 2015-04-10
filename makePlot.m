for i=1:10

fileID = fopen(sprintf('%s%d%s', 'plot', i,'.txt'),'r');
formatSpec = '%f %f';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);

A = A';

X = A(:,1);
Y = A(:,2);
figure;
plot(X,Y,'-');
end
