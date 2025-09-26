#include "raylib.h"


void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint)
{
    if ((texture.id <= 0) || (scale <= 0.0f)) return; 
    if ((source.width == 0) || (source.height == 0)) return;

    int tileWidth = (int)(source.width * scale), tileHeight = (int)(source.height * scale);
    if ((dest.width < tileWidth) && (dest.height < tileHeight))
    {
      
        DrawTexturePro(texture, { source.x, source.y, ((float)dest.width / tileWidth) * source.width, ((float)dest.height / tileHeight) * source.height },
             {
            dest.x, dest.y, dest.width, dest.height
             }, origin, rotation, tint);
    }
    else if (dest.width <= tileWidth)
    {
        
        int dy = 0;
        for (; dy + tileHeight < dest.height; dy += tileHeight)
        {
            DrawTexturePro(texture, { source.x, source.y, ((float)dest.width / tileWidth) * source.width, source.height }, { dest.x, dest.y + dy, dest.width, (float)tileHeight }, origin, rotation, tint);
        }

        
        if (dy < dest.height)
        {
            DrawTexturePro(texture, { source.x, source.y, ((float)dest.width / tileWidth) * source.width, ((float)(dest.height - dy) / tileHeight) * source.height },
                 {
                dest.x, dest.y + dy, dest.width, dest.height - dy
                 }, origin, rotation, tint);
        }
    }
    else if (dest.height <= tileHeight)
    {
       
        int dx = 0;
        for (; dx + tileWidth < dest.width; dx += tileWidth)
        {
            DrawTexturePro(texture, { source.x, source.y, source.width, ((float)dest.height / tileHeight) * source.height }, { dest.x + dx, dest.y, (float)tileWidth, dest.height }, origin, rotation, tint);
        }

       
        if (dx < dest.width)
        {
            DrawTexturePro(texture, { source.x, source.y, ((float)(dest.width - dx) / tileWidth) * source.width, ((float)dest.height / tileHeight) * source.height },
                 {
                dest.x + dx, dest.y, dest.width - dx, dest.height
                 }, origin, rotation, tint);
        }
    }
    else
    {
       
        int dx = 0;
        for (; dx + tileWidth < dest.width; dx += tileWidth)
        {
            int dy = 0;
            for (; dy + tileHeight < dest.height; dy += tileHeight)
            {
                DrawTexturePro(texture, source, { dest.x + dx, dest.y + dy, (float)tileWidth, (float)tileHeight }, origin, rotation, tint);
            }

            if (dy < dest.height)
            {
                DrawTexturePro(texture, { source.x, source.y, source.width, ((float)(dest.height - dy) / tileHeight) * source.height },
                     {
                    dest.x + dx, dest.y + dy, (float)tileWidth, dest.height - dy
                     }, origin, rotation, tint);
            }
        }

      
        if (dx < dest.width)
        {
            int dy = 0;
            for (; dy + tileHeight < dest.height; dy += tileHeight)
            {
                DrawTexturePro(texture, { source.x, source.y, ((float)(dest.width - dx) / tileWidth) * source.width, source.height },
                     {
                    dest.x + dx, dest.y + dy, dest.width - dx, (float)tileHeight
                     }, origin, rotation, tint);
            }

           
            if (dy < dest.height)
            {
                DrawTexturePro(texture, { source.x, source.y, ((float)(dest.width - dx) / tileWidth) * source.width, ((float)(dest.height - dy) / tileHeight) * source.height },
                     {
                    dest.x + dx, dest.y + dy, dest.width - dx, dest.height - dy
                     }, origin, rotation, tint);
            }
        }
    }
}
