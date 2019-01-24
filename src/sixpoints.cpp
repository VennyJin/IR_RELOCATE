


void bubble_sorty(vector<Point2f> &arr, int len)
{
	if (len > 1)
	{
		int i, j;
		for (i = 0; i < len - 1; i++)    //Íâ²ãÑ­»·¿ØÖÆÌËÊý£¬×ÜÌËÊýÎªlen-1
			for (j = 0; j < len - 1 - i; j++)  //ÄÚ²ãÑ­»·Îªµ±Ç°iÌËÊý ËùÐèÒª±È½ÏµÄ´ÎÊý
				if (arr[j].y > arr[j + 1].y)
					swap(arr[j], arr[j + 1]);
	}
}
void bubble_sortx(vector<Point2f> &arr, int len)
{
	if (len > 1)
	{
		int i, j;
		for (i = 0; i < len - 1; i++)    //Íâ²ãÑ­»·¿ØÖÆÌËÊý£¬×ÜÌËÊýÎªlen-1
			for (j = 0; j < len - 1 - i; j++)  //ÄÚ²ãÑ­»·Îªµ±Ç°iÌËÊý ËùÐèÒª±È½ÏµÄ´ÎÊý
				if (arr[j].x > arr[j + 1].x)
					swap(arr[j], arr[j + 1]);
	}
}
