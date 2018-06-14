<?php

	session_start();

	if(!isset($_SESSION["name"])){
		header("location:/tcc");
	}
	else{
		$name = $_SESSION["name"];
	}


?>
