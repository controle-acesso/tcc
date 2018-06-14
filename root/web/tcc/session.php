<?php

	session_start();

	if(!isset($_SESSION["name"])){
		header("location:http://localhost/tcc");
	}
	else{
		$name = $_SESSION["name"];
	}


?>