# MagicWords

**header-only console game library**

Define `MAGICWORDS_IMPLEMENTATION` to enable function definition, for example:
```cpp
#define MAGICWORDS_IMPLEMENTATION
#include "MagicWords.h"
```

Supported functions:
```cpp
MW_Stage* MW_CreateStage(int width, int height);
void MW_ClearStage(MW_Stage* stage, char c);
void MW_RenderStage(const MW_Stage* stage);
void MW_DestroyStage(MW_Stage* stage);

MW_Sprite* MW_CreateSprite(const char** content, int width, int height);
void MW_DestroySprite(MW_Sprite* sprite);

void MW_CopySprite(MW_Stage* stage, const MW_Sprite* sprite, const MW_Rect* src, const MW_Point* dst);

int MW_GetInput(int* input);     // only for Windows
```
