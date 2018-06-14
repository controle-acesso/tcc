<!DOCTYPE html>
<html>
<title>Login</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://www.w3schools.com/lib/w3-theme-red.css">
<body>

<div class="w3-card-4">
  <header class="w3-container w3-theme">
    <h2>Login</h2>
  </header>  
  <form class="w3-container" action="/tcc/login.php" method="post">
    <p>      
    <label><b>Login</b></label>
    <input class="w3-input w3-border w3-sand" name="login" type="text"></p>
    <p>      
    <label><b>Senha</b></label>
    <input class="w3-input w3-border w3-sand" name="password" type="password"></p>
    <p>
    <input class="w3-input w3-border" type="submit" value="Entrar">
  </form>
  <footer class="w3-container w3-theme w3-margin-top">
    <h3>Controle de acesso</h3>
  </footer>
</div>

</body>
</html> 
