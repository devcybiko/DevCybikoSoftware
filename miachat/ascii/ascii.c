#include <stdio.h>

main()
{
	int c;

	for (c=0; c<256; c++)
	{
		if (c%16==0) printf("%d: ", c);
		printf("%c ", c);
		if (c%16==15) printf("\n");
	}
}