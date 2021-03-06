/*------------------------------------------------------------------.
| Copyright 2001  Alexandre Duret-Lutz <duret_g@epita.fr>           |
|                                                                   |
| This file is part of Heroes.                                      |
|                                                                   |
| Heroes is free software; you can redistribute it and/or modify it |
| under the terms of the GNU General Public License version 2 as    |
| published by the Free Software Foundation.                        |
|                                                                   |
| Heroes is distributed in the hope that it will be useful, but     |
| WITHOUT ANY WARRANTY; without even the implied warranty of        |
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU |
| General Public License for more details.                          |
|                                                                   |
| You should have received a copy of the GNU General Public License |
| along with this program; if not, write to the Free Software       |
| Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA          |
| 02111-1307 USA                                                    |
`------------------------------------------------------------------*/

#include "system.h"
#include "lvl_priv.h"
#include "access.h"
#include "xstrduplwr.h"

void
decode_level_header (const a_u8 *data, a_level *lvl)
{
  /* Structure of the header:

     Offset  Size  Repeat  What
     --------------------------------------------------------------------
      0      4             width of the level in tiles
      4      4             height of the level in tiles
      8      4             horizontal wrapping AND-mask
     12      4             vertical wrapping AND-mask
     16      4     4       starting tile index for each player
     32      1     4       starting direction (upper 4 bits) and starting
                           square (bottom 4 bits) for each player
     36      9             tile sprite map basename (zero-terminated)
     45      9             sound track alias (zero-terminated)
     54      1     10      unused bytes.
     ==
     64 bytes.
  */
  int player;
  a_u32 starting_tile_index[4];

  READ_U32 (data, lvl->tile_width);
  READ_U32 (data, lvl->tile_height);
  READ_U32 (data, lvl->tile_width_wrap);
  READ_U32 (data, lvl->tile_height_wrap);

  for (player = 0; player < 4; ++player)
    READ_U32 (data, starting_tile_index[player]);
  for (player = 0; player < 4; ++player) {
    a_u8 starting_dir;
    a_square_coord y, x;

    READ_U8 (data, starting_dir);
    /* Compute the square starting position for each player.  */
    y = (starting_tile_index[player] / lvl->tile_width) * 2;
    x = (starting_tile_index[player] % lvl->tile_width) * 2;
    /* The bottom bits of starting_dir holds the starting square
       index in the tile.  */
    if (starting_dir & 1)
      ++x;
    if (starting_dir & 2)
      ++y;
    lvl->private->start_pos[player].y = y;
    lvl->private->start_pos[player].x = x;
    /* The upper bits of starting_dir actually holds the direction.  */
    lvl->private->start_dir[player] = starting_dir >> 4;
  }

  lvl->private->tile_sprite_map_basename = xstrduplwr ((const char *) data);
  data += 9;
  lvl->private->sound_track_alias = xstrdup ((const char *) data);
}
