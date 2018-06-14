<!DOCTYPE html>

<?php 
  include('session.php');
?>

<html>
  <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.6.9/angular.min.js"></script>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3mobile.css">
  <link rel="stylesheet" href="https://www.w3schools.com/lib/w3-theme-red.css">
  <body>
    <nav class="w3-sidebar w3-bar-block w3-card" id="menu">
          <div class="w3-container w3-theme-d2">
            <span onclick="closeSidebar()" class="w3-button w3-display-topright w3-large">X</span>
            <br>
            <div class="w3-center w3-padding">
                <h3>Opções</h3>
            </div>
          </div>
        <a class="w3-bar-item w3-button" href="/tcc/adm.php">Início</a>
        <a class="w3-bar-item w3-button" href="/tcc/newuser.php">Novo Usuário</a>
        <a class="w3-bar-item w3-button" href="/tcc/rfid.php">Novo RFID</a>
        <a class="w3-bar-item w3-button" href="/tcc/logout.php">Sair</a>
      </nav>
    <header class="w3-bar w3-theme">
      <button class="w3-bar-item w3-button w3-xxxlarge" onclick="openSidebar()">&#9776;</button>
      <h1 class="w3-bar-item">Novo Usuário</h1>
    </header>
    <div class="w3-container">
      <form ng-app="formApp" ng-controller="formCtrl" name="newuserForm" class="w3-container" action="addnewuser.php" method="post" onsubmit="return validateForm()">
        <label>Nome:</label>
        <input class="w3-input w3-border" placeholder="Nome" type="text" name="name" required>
        <label>CPF:</label>
        <input class="w3-input w3-border" type="text" placeholder="CPF (somente números)" name="cpf" size="11" maxlength="11" required>
        <p><select class="w3-select w3-border" name="option" required>
          <option value="" disabled selected>Escolha seu cartão</option>
          <option ng-repeat="x in names">{{x.tag_id}}</option>
        </select></p>
        <div class="w3-cell-row">
          <div class="w3-cell">
            <input class="w3-input" type="submit" value="Adicionar">
          </div>
          <div class="w3-cell">
            <input class="w3-input" type="reset" value="Limpar">
          </div>
        </div>        
      </form>
    </div>    
    <footer class="w3-margin-top w3-container w3-theme">      
      <h3>Controle de acesso</h3>
    </footer>
    <script>
          closeSidebar();
          var app = angular.module('formApp', []);
          app.controller('formCtrl', function($scope, $http){            
            $http.get("unusedTag.php").then(function (response) {$scope.names = response.data;});
          });
          function validateForm(){
            var newcpf = document.forms["newuserForm"]["cpf"].value;
            if(newcpf.length < 11){
              alert("CPF deve conter 11 digitos");
              return false;
            }
            if(isNaN(Number(newcpf))){
              alert("CPF deve conter apenas números");
              return false;
            }
            return true;
          }
          function openSidebar(){
            document.getElementById("menu").style.display = "block";
          }
          function closeSidebar(){
            document.getElementById("menu").style.display = "none";
          }
    </script>
  </body>
</html>
