<!DOCTYPE html>

<?php 
  include('session.php');
    
?>

<html>
<title>Acesso</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://www.w3schools.com/lib/w3-theme-red.css">
<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
	<body>

		<nav class="w3-sidebar w3-bar-block w3-card" id="menu">
      		<div class="w3-container w3-theme-d2">
        		<span onclick="closeSidebar()" class="w3-button w3-display-topright w3-large">X</span>
        		<br>
        		<div class="w3-center w3-padding">
          			<h3>Opções</h3>
        		</div>
      		</div>
        <a class="w3-bar-item w3-button" href="http://localhost/tcc/user.php">Início</a>
        <a class="w3-bar-item w3-button" href="http://localhost/tcc/edituser.html">Editar perfil</a>    	
      	<a class="w3-bar-item w3-button" href="http://localhost/tcc/logout.php">Sair</a>
    	</nav>
		<header class="w3-bar w3-theme">
			<button class="w3-bar-item w3-button w3-xxxlarge" onclick="openSidebar()">&#9776;</button>
			<h1 class="w3-bar-item"><?php echo $name; ?></h1>
		</header>
		<div class="w3-container">
			<p><button class="w3-btn w3-blue-grey" onclick="openLock()">Abrir porta</button></p>
			<p><button class="w3-btn w3-blue-grey" onclick="">Desligar alarme</button></p>			
		</div>		
	 	<footer class="w3-margin-top w3-container w3-theme">			
			<h3>Controle de acesso</h3>
		</footer>
		<script>
	      closeSidebar();	      
	      function openSidebar(){
	        document.getElementById("menu").style.display = "block";
	      }
	      function closeSidebar(){
	        document.getElementById("menu").style.display = "none";
	      }
	      function openLock() {
			  var xhttp;		  
			  xhttp = new XMLHttpRequest();			  		  
			  xhttp.open("GET", "openLock.php", true);
			  xhttp.send();   
			}          
    	</script>
	</body>
</html>
