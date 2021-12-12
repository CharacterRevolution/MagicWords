#ifndef _MAGIC_WORDS_H_
#define _MAGIC_WORDS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#endif // _WIN32

#ifdef __cplusplus
#define MW_API	extern "C"
#include <algorithm>
using std::min; using std::max;
#else
#define MW_API
#endif // __cplusplus

typedef struct MW_Point
{
	int x, y;
} MW_Point;

typedef struct MW_Rect
{
	int x, y;
	int w, h;
} MW_Rect;

typedef struct MW_Stage MW_Stage;
typedef struct MW_Sprite MW_Sprite;

MW_API MW_Stage* MW_CreateStage(int width, int height);
MW_API void MW_ClearStage(MW_Stage* stage, char c);
MW_API void MW_RenderStage(const MW_Stage* stage);
MW_API void MW_DestroyStage(MW_Stage* stage);

MW_API MW_Sprite* MW_CreateSprite(const char** content, int width, int height);
MW_API void MW_DestroySprite(MW_Sprite* sprite);

MW_API void MW_CopySprite(MW_Stage* stage, const MW_Sprite* sprite, const MW_Rect* src, const MW_Point* dst);

#ifdef _WIN32
MW_API int MW_GetInput(int* input);
#endif // _WIN32

#ifdef MAGICWORDS_IMPLEMENTATION

struct MW_Stage{
	int width, height;
	char** content;
};

struct MW_Sprite
{
	int width, height;
	char** content;
};

MW_Stage* MW_CreateStage(int width, int height)
{
	if (!width || !height) return NULL;

	MW_Stage* pStage = (MW_Stage*)malloc(sizeof(MW_Stage));
	if (!pStage) return NULL;

	pStage->width = width, pStage->height = height;
	pStage->content = (char**)malloc(sizeof(char*) * height);
	if (!pStage->content) { free(pStage); return NULL; }
	memset(pStage->content, '\0', sizeof(char*) * height);

	for (int i = 0; i < height; ++i)
	{
		pStage->content[i] = (char*)malloc(sizeof(char) * (width + 1));

		if (!pStage->content[i])
		{
			for (int j = 0; j < i; ++j)
				free(pStage->content[i]);
			free(pStage->content);
			free(pStage);
			return NULL;
		}

		memset(pStage->content[i], '\0', sizeof(char) * (width + 1));
	}

	return pStage;
}

void MW_ClearStage(MW_Stage* stage, char c)
{
	if (!stage) return;

	for (int i = 0; i < stage->width; i++)
		for (int j = 0; j < stage->height; j++)
			stage->content[j][i] = c;
}

void MW_DestroyStage(MW_Stage* stage)
{
	if (!stage) return;

	for (int i = 0; i < stage->height; ++i)
		free(stage->content[i]);

	free(stage->content);
	free(stage);
}

MW_Sprite* MW_CreateSprite(const char** content, int width, int height)
{
	if (!width || !height) return NULL;

	MW_Sprite* pSprite = (MW_Sprite*)malloc(sizeof(MW_Sprite));
	if (!pSprite) return NULL;

	pSprite->width = width, pSprite->height = height;
	pSprite->content = (char**)malloc(sizeof(char*) * height);
	if (!pSprite->content) { free(pSprite); return NULL; }
	memset(pSprite->content, '\0', sizeof(char*) * height);

	for (int i = 0; i < height; ++i)
	{
		pSprite->content[i] = (char*)malloc(sizeof(char) * (width + 1));

		if (!pSprite->content[i])
		{
			for (int j = 0; j < i; ++j)
				free(pSprite->content[i]);
			free(pSprite->content);
			free(pSprite);
			return NULL;
		}

		memset(pSprite->content[i], '\0', sizeof(char) * (width + 1));
		memcpy(pSprite->content[i], content[i], sizeof(char) * width);
	}

	return pSprite;
}

void MW_DestroySprite(MW_Sprite* sprite)
{
	if (!sprite) return;

	for (int i = 0; i < sprite->height; ++i)
		free(sprite->content[i]);

	free(sprite->content);
	free(sprite);
}

void MW_CopySprite(MW_Stage* stage, const MW_Sprite* sprite, const MW_Rect* src, const MW_Point* dst)
{
	if (!stage || !sprite || !dst || dst->x > stage->width - 1 || dst->y > stage->height - 1) return;
	
	int src_x = src ? max(src->x, 0) : 0;
	int src_y = src ? max(src->y, 0) : 0;
	int src_w = src ? min(src->w, sprite->width) : sprite->width;
	int src_h = src ? min(src->h, sprite->height) : sprite->height;

	if (dst->x + src_w < 0 || dst->y + src_h < 0) return;

	for (int i = 0; i < min(src_h, stage->height - dst->y); i++)
		memcpy(stage->content[max(0, dst->y + i)] + dst->x, sprite->content[src_x + i], sizeof(char) * min(src_w, stage->width - dst->x));
}

void MW_RenderStage(const MW_Stage* stage)
{
	if (!stage) return;

	for (int i = 0; i < stage->height; i++)
		printf("%s\n", stage->content[i]);
}

#ifdef _WIN32
int MW_GetInput(int* input)
{
	if (_kbhit())
	{
		*input = _getch();
		return 1;
	}

	return 0;
}
#endif // _WIN32

#endif // MAGICWORDS_IMPLEMENTATION

#endif // !_MAGIC_WORDS_H_
