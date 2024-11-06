CC := gcc

# $@ 是目标文件的名称，这里是第一个 fopen_test
# $^ 是后面的依赖名，这里是 fopen_test.c
fopen_test: fopen_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fclose_test: fclose_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fputc_test: fputc_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fputs_test: fputs_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fprintf_test: fprintf_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fgetc_test: fgetc_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fgets_test: fgets_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
	
fscanf_test: fscanf_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

stdin_out_err_test: stdin_out_err_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unistd: unistd.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

system_call_test: system_call_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@