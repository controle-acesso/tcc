<!DOCTYPE html>

<?php 
  include('session.php');
?>

<html>

  <meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.6.9/angular.min.js"></script>
	<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3mobile.css">
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
        <a class="w3-bar-item w3-button" href="http://localhost/tcc/adm.php">Início</a>
      	<a class="w3-bar-item w3-button" href="http://localhost/tcc/newuser.php">Novo Usuário</a>
      	<a class="w3-bar-item w3-button" href="http://localhost/tcc/rfid.php">Novo RFID</a>
      	<a class="w3-bar-item w3-button" href="http://localhost/tcc/logout.php">Sair</a>
    	</nav>
		<header class="w3-bar w3-theme">
			<button class="w3-bar-item w3-button w3-xxxlarge" onclick="openSidebar()">&#9776;</button>
			<h1 class="w3-bar-item"><?php echo $name; ?></h1>
		</header>
    <div ng-app="cardApp" ng-controller="cardCtrl" class="w3-container">
      <div class="w3-container w3-margin">        
        <div class="w3-cell-row">
          <div class="w3-cell w3-cell-middle">
            <input class="w3-input w3-padding w3-border" type="text" placeholder="Procurar por usuários..." ng-model="search">         
          </div>
          <div class="w3-cell w3-center w3-cell-middle">
            <span class="w3-xxlarge material-icons">search</span>
          </div>
        </div>
      </div>
      <div class="w3-container">
        <div ng-repeat="x in names | filter:search " class="w3-card w3-margin w3-teal">
          <div class="w3-cell-row">
            <div class="w3-cell w3-cell-middle">            
              <div class="w3-container w3-margin">
                <span>Nome: {{x.name}}</span>
              </div>
              <div class="w3-container w3-margin">
                <span>RFID tag: {{x.tag_id}}</span>
              </div>
            </div>
            <div class="w3-cell w3-right">
              <a class="w3-btn material-icons" href="#">more_vert</a>
            </div>
          </div>
        </div>
      </div>   
    </div>
		<footer class="w3-margin-top w3-container w3-theme">			
			<h3>Controle de acesso</h3>
		</footer>
		<script>
      closeSidebar();

      var appCard = angular.module('cardApp',[]);
      appCard.controller('cardCtrl', function($scope, $http){
        $http.get("userList.php").then(function (response) {$scope.names = response.data;});
      });
      
      function openSidebar(){
        document.getElementById("menu").style.display = "block";
      }
      function closeSidebar(){
        document.getElementById("menu").style.display = "none";
      }

    </script>
	</body>
</html>