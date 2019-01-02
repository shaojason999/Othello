extern unsigned int hash_function(unsigned long long int board);
extern unsigned long long int board[3];

void init_hash_table()
{
	unsigned int index;
	index=hash_function(0x0000001008000000+0x0000000810000000);	//white+black
	hash[index]=(3<<4)+4;
	index=hash_function(0x0000000008000000+0x0000101810000000);
	hash[index]=(5<<4)+3;
	index=hash_function(0x0000000008000000+0x0000003810000000);
	hash[index]=(3<<4)+5;
	index=hash_function(0x0000001000000000+0x0000000818080000);
	hash[index]=(4<<4)+6;
	index=hash_function(0x0000001000000000+0x000000081c000000);
	hash[index]=(6<<4)+6;
/*
	index=hash_function(
	hash[index]=

	index=hash_function(0x0000000038000000+0x0000101800000000);
	hash[index]=6<<4+5;
	index=hash_function(0x0000000030000000+0x0000101808080000);
	hash[index]=2<<4+4;
*/
}
