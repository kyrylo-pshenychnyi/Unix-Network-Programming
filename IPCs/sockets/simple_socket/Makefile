all: srv cli

srv: 
	gcc server.c -o srv
	
cli: 
	gcc client.c -o cli

srv_0_port:
	gcc server_with_0_port_num.c -o srv_0_port

clean: 
	@echo clean
	@rm -rf cli srv srv_0_port
