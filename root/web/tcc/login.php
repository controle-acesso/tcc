<?php	
	
	session_start();

	if($_SERVER["REQUEST_METHOD"] == "POST"){

		$login = format_data($_POST["login"]);
		$password = format_data($_POST["password"]);

		$mysql = new mysqli("localhost","tcc","tcc","tccDB");
		$result = $mysql->query("select func,name from user where login='$login' and password='$password';");

		if($result->num_rows > 0){

			$row = $result->fetch_assoc();

			$_SESSION["name"] = $row["name"];
			$_SESSION["func"] = $row["func"];
			
			if($row["func"] == "admin"){				
				header('location:http://localhost/tcc/adm.php');
			}
			else{
				header('location:http://localhost/tcc/user.php');
			}		
		}
		else{
			header('location:http://localhost/tcc/');
		}
	}
	else{
			header('location:http://localhost/tcc/');
		}
	
	function format_data($data){
		$data = trim($data);
		$data = stripslashes($data);
		$data = htmlspecialchars($data);
		return $data;
	}
	

?>