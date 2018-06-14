<?php
	
	session_start();

	if($_SERVER["REQUEST_METHOD"] == "GET"){

		if($_SESSION["func"] == "admin"){

			$mysql = new mysqli("localhost","tcc","tcc","tccDB");
			$result = $mysql->query("select user.name, user_tag.tag_id from user inner join user_tag on user.user_id = user_tag.user_id;");
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
			header("location:/tcc/");
		}
	}
	else{
			header("location:/tcc/");
		}
?>
