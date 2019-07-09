if [ -z "$2" ]
then
	rm $2;
fi
./asm $1;
hexdump -C $2 > b;
echo "--------------------------------\n";
rm $2;
./a2 $1;
hexdump -C $2 > c;
diff b c;
rm b c;
