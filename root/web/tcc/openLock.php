<?php
	$socket = socket_create(AF_UNIX,SOCK_STREAM,0);
	// $command = "chown root:root /temp/programManager.socket";
	// exec($command);
	$addr = "/tmp/programManager.socket";
	if($socket == false){
		echo "socket_create() failed".socket_strerror(socket_last_error());
	}
	$result = socket_connect($socket,$addr,0);
	if($result == false){
		echo "socket_connect() failed:".socket_strerror(socket_last_error());
	}
	$msg = "04";
	socket_write($socket, $msg, strlen($msg));
	echo $msg;
	socket_close($socket);

?>