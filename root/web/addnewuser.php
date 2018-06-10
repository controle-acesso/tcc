<?php
	
	include('session.php');

	if($_SERVER["REQUEST_METHOD"] == "POST" && $_SESSION["func"] == "admin"){

		$login = format_data($_POST['cpf']);
		$tag_id = $_POST['option'];	
		$name = format_data($_POST['name']);
		$password = "12345678";		

		$mysql = new mysqli("localhost","tcc","tcc","tccDB");
		$result = $mysql->query("select user_id from user where login='$login'");
		if($result->num_rows > 0){
			
		}	
		else{
			$result = $mysql->query("insert into user(name, login, password) values('$name','$login','$password');");
			$result = $mysql->query("select user_id from user where login='$login';");
			$row = $result->fetch_assoc();
			$user_id = $row["user_id"];
			$result = $mysql->query("insert into user_tag(user_id, tag_id) values('$user_id','$tag_id');");
		}
		$mysql->close();
		header('location:http://localhost/tcc/newuser.php');
		
	}
	else{
		header("location:http://localhost/tcc/");
	}

	function format_data($data){
		$data = trim($data);
		$data = stripslashes($data);
		$data = htmlspecialchars($data);
		return $data;
	}
?>