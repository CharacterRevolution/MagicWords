# MagicWords

**header-only console game library**

Define `MAGICWORDS_IMPLEMENTATION` to enable function definition, for example:
```cpp
#define MAGICWORDS_IMPLEMENTATION
#include "MagicWords.h"
```

Supported functions:
```cpp
MW_API MW_Stage* MW_CreateStage(int width, int height);
MW_API void MW_ClearStage(MW_Stage* stage, char c);
MW_API void MW_RenderStage(const MW_Stage* stage);
MW_API void MW_DestroyStage(MW_Stage* stage);

MW_API MW_Sprite* MW_CreateSprite(const char** content, int width, int height);
MW_API void MW_DestroySprite(MW_Sprite* sprite);

MW_API void MW_CopySprite(MW_Stage* stage, const MW_Sprite* sprite, const MW_Rect* src, const MW_Point* dst);

MW_API int MW_GetInput(int* input);     // only for Windows
```