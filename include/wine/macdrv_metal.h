/*
 * Native Metal surface bridge for the Mac driver
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_MACDRV_METAL_H
#define __WINE_MACDRV_METAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct macdrv_metal_surface_data *macdrv_metal_surface;
typedef void (*macdrv_metal_main_callback)(void *context);

/* Native host API. The HWND is its 32-bit USER handle; all other pointers are
 * native pointers and must not be passed directly through a PE32 ABI.
 * Creation accepts a live same-process top-level window with a native window,
 * and must not run on the AppKit main thread. The caller keeps the device
 * alive until this call returns. Failure returns NULL and clears the layer.
 * The returned layer is borrowed for the lifetime of the owned surface.
 */
macdrv_metal_surface macdrv_metal_surface_create_v1(uint32_t hwnd, void *metal_device,
                                                   void **borrowed_metal_layer);

/* Refresh Wine geometry and select the surface for presentation. Returns zero
 * after detachment. A later detach does not invalidate the owned view/layer.
 */
int macdrv_metal_surface_prepare_v1(macdrv_metal_surface surface);

/* Consume the surface after all its users have finished. NULL is allowed. */
void macdrv_metal_surface_release_v1(macdrv_metal_surface surface);

/* Run synchronously on Wine's query-aware AppKit request source, or directly
 * when already on AppKit main. The callback may only operate on retained
 * Metal/layer objects; it must not enter Wine window or client-surface APIs.
 * The caller must not hold Wine window or client-surface locks.
 */
void macdrv_metal_run_on_main_v1(macdrv_metal_main_callback callback, void *context);

#ifdef __cplusplus
}
#endif

#endif /* __WINE_MACDRV_METAL_H */
