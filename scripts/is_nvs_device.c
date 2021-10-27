#include "../include/nvs.h"
#include <stddef.h>

int main(int argc, char *argv[]) {
	return !nvs_check_descriptor(argv[1], NULL);
}
