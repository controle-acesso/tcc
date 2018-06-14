<?php
	
	include('session.php');

	if($_SERVER["REQUEST_METHOD"] == "POST" && $_SESSION["func"] == "admin"){

		$rfid = $_POST['rfid'];	

		$mysql = new mysqli("localhost","tcc","tcc","tccDB");
		$result = $mysql->query("insert into tag(tag_id) values('$rfid');");	
		$mysql->close();
		header("location:/tcc/rfid.php");
		
	}
	else{
		header("location:/tcc/");
	}
?>
