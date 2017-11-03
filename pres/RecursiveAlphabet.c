void appel(int64_t val){
	int64_t val2 = val + 1;
	putchar(val);
	putchar(13);
	putchar(10);
	if(val != 90){
		appel(val2);
	}
	else{	
	}
}

void main ( void )
{
	int64_t val = 65;
	appel(val);
}
