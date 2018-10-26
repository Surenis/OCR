#include <stdio.h>
#include <stdlib.h>

unsigned char **CreateAMatrix(int width, int height)
{
	unsigned char **matrix =
		(unsigned char **)malloc(sizeof(unsigned char *) * height);
	for (int i = 0; i < height; i++)
	{
		*(matrix + i) = (unsigned char *)malloc(sizeof(unsigned char) * width);
	}
	return matrix;
}

int **CreateAMatrixInt(int width, int height)
{
	int **matrix =
		(int **)malloc(sizeof(int *) * height);
	for (int i = 0; i < height; i++)
	{
		*(matrix + i) = (int *)malloc(sizeof(int) * width);
	}
	return matrix;
}

int GetNumberHorizontalWhiteNeighbors(unsigned char **array, int x, int y, int maxPos)
{
	int count = 0;
	int i = x + 1;
	while (i < maxPos && array[y][i] == 0)
	{
		count++;
		i++;
	}

	i = x;
	while (i > 0 && array[y][i] == 0)
	{
		count++;
		i--;
	}
	return count;
}

int GetNumberVerticalWhiteNeighbors(unsigned char **array, int x, int y, int maxPos)
{
	int count = 0;
	int i = y + 1;
	while (i < maxPos && array[i][x] == 0)
	{
		count++;
		i++;
	}
	i = y;
	while (i > 0 && array[i][x] == 0)
	{
		count++;
		i--;
	}
	return count;
}

unsigned char **DetectBlocks(unsigned char **binarizedImageMatrix, int imageWidth, int imageHeight)
{
	// if white space > 4 => two different blocs
	int horizontalStep = 12; 
	int verticalStep = 30; 
	unsigned char **horizontalResult = CreateAMatrix(imageWidth, imageHeight);
	unsigned char **verticalResult = CreateAMatrix(imageWidth, imageHeight);
	unsigned char **combinedResult = CreateAMatrix(imageWidth, imageHeight);
	unsigned char **finalResult = CreateAMatrix(imageWidth, imageHeight);

	// Horizontal pass
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(binarizedImageMatrix[y][x] == 0)
			{
				int n = GetNumberHorizontalWhiteNeighbors(binarizedImageMatrix, x, y, imageWidth);
				if(n <= horizontalStep)
				{
					horizontalResult[y][x] = 1;
				} else {
					horizontalResult[y][x] = 0;
				}
			} else {
				horizontalResult[y][x] = 1;
			}
		}
	}

	// Vertical pass
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(binarizedImageMatrix[y][x] == 0)
			{
				int n = GetNumberVerticalWhiteNeighbors(binarizedImageMatrix, x, y, imageHeight);
				if(n <= verticalStep)
				{
					verticalResult[y][x] = 1;
				} else {
					verticalResult[y][x] = 0;
				}
			} else {
				verticalResult[y][x] = 1;
			}
		}
	}

	// Combine both results
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(horizontalResult[y][x] == 0 && verticalResult[y][x] == 0)
			{
				combinedResult[y][x] = 0;
			}
			else
			{
				combinedResult[y][x] = 1;
			}
		}
	}
	
	// Smoothing
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(combinedResult[y][x] == 0)
			{
				int n = GetNumberHorizontalWhiteNeighbors(combinedResult, x, y, imageWidth);
				if(n <= horizontalStep)
				{
					finalResult[y][x] = 1;
				} else {
					finalResult[y][x] = 0;
				}
			} else {
				finalResult[y][x] = 1;
			}
		}
	}

	return finalResult;
}






void Labeling(unsigned char **matrix, int x, int y, int width, int height, int *xMin, int *yMin, int *xMax, int *yMax, int k)
{
	if(x >= width || x < 0 || y < 0 || y >= height || matrix[y][x] != 1)
	{
		return;
	}

	if(x > *xMax)
	{
		*xMax = x;
	}
	if(y > *yMax)
	{
		*yMax = y;
	}
	if(x < *xMin)
	{
		*xMin = x;
	}
	if(y < *yMin)
	{
		*yMin = y;
	}

	matrix[y][x] = k;
	Labeling(matrix, x + 1, y, width, height, xMin, yMin, xMax, yMax, k);
	Labeling(matrix, x - 1, y, width, height, xMin, yMin, xMax, yMax, k);
	Labeling(matrix, x, y + 1, width, height, xMin, yMin, xMax, yMax, k);
	Labeling(matrix, x, y - 1, width, height, xMin, yMin, xMax, yMax, k);
}

int **GetBlocks(unsigned char** matrix, int imageWidth, int imageHeight)
{
	int i = 0;
	int k = 2;
	int xMin, yMin, xMax, yMax;
	int **blocks = CreateAMatrixInt(100, 1);
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(matrix[y][x] == 1)
			{
				xMin = x;
				yMin = y;
				xMax = x;
				yMax = y;
				Labeling(matrix, x, y, imageWidth, imageHeight, &xMin, &yMin, &xMax, &yMax, k);
				blocks[0][i] = xMin;
				blocks[0][i + 1] = yMin;
				blocks[0][i + 2] = xMax;
				blocks[0][i + 3] = yMax;
				i += 4;
				k++;
			}
		}
	}

	return blocks;
}

/*

To do

- Fix sticky to borders
- Fix problem blocks size
- LinesDetection

*/