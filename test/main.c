#include "mlx.h"
#include <stdlib.h>

#define EVENT_KEY_PRESSED 2
#define MASK_KEY_PRESSED (1L<<0)
#define KEY_ESC 65307

int key_hook(int key, void *arg)
{	
	if (key == KEY_ESC)
		exit(1);	
}

int exit_func(void)
{
	exit(1);
}

int main(void)
{
	void *mlx_ptr = mlx_init();
	void *win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Title of the window");
	mlx_hook(win_ptr, EVENT_KEY_PRESSED, MASK_KEY_PRESSED, &key_hook, NULL);
	mlx_loop(mlx_ptr);
	return (0);
	
}
