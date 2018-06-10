<?php

	session_start();

	if($_SERVER["REQUEST_METHOD"] == "GET" && $_SESSION["func"] == "admin"){

		$mysql = new mysqli("localhost","tcc","tcc","tccDB");
		$result = $mysql->query("select tag_id from tag where tag_id not in (select tag_id from user_tag);");
		if($result->num_rows > 0){
			$dbdata = array();
			while ( $row = $result->fetch_assoc()){
				$dbdata[]=$row;
	  		}
			echo json_encode($dbdata);
		}	
		$mysql->close();
	}
	else{
		header("location:http://localhost/tcc/");
	}
?>