<!DOCTYPE html>

<?php 
  include('session.php');
?>

<html>
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
      <h1 class="w3-bar-item">RFID</h1>
    </header>
    <div class="w3-container">
      <form name="rfidForm" class="w3-container" action="newrfid.php" method="post" onsubmit="return validateForm()">
        <labe>RFID Tag:</labe>
        <input class="w3-input w3-border" placeholder="Núme da tag em hex" type="text" name="rfid" maxlength="8" size="8">
        <p><input class="w3-input" type="submit" value="Adicionar"></p>
      </form>   
    </div> 
    <footer class="w3-margin-top w3-container w3-theme">      
      <h3>Controle de acesso</h3>
    </footer>
    <script>
          closeSidebar();
          function validateForm(){
            var rfid = document.forms["rfidForm"]["rfid"].value;
            if(rfid.length < 8){
              alert("RFID tag deve ter 8 digitos");
              return false;
            }
            rfid = "0x" + rfid;
            rfid = Number(rfid);
            if(isNaN(rfid)){
              alert("RFID tag deve ser hexadecimal");
              return false;
            }
            else{              
              return true;
            }
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
