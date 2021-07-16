
//webpagecode
String pageData(IPAddress ip){
const char webpageCode[] = 
R"====(
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
  <!--- CSS --------->
  <style>
  .column {
    display:flex;
    flex-direction:column;
  }
  .row {
    display:flex;
    flex-direction:row;
  }
  .container{
    width:100%;
    height:100%;
  }
  input[type="button"], input[type="submit"],input[type="text"],input[type="password"]{
    min-width:100px;
    padding:5px;
  }
  .all-center{
    align-items:center;
    align-content:center;
    justify-content:center;
  }
  .align-center{
    align-items:center;
    align-content:center;
  }
  .justify-center{
    justify-content:center;
  }
  .input-holder{
    min-width:200px;
    min-height:200px;
    padding:10px;
    background-color:white;
  }
  body{
    min-height:90vh;
    background:whitesmoke
  }
  .d-flex{
    display:flex;
  }
  .inherit-h{
    height:inherit !important;
  }
  label{
    font-size:12px;
  }

  .mt-10{
    margin-top:10px;
  }

  :root{
    font-family:sans-serif;
  }
  .bold{
    font-weight:bold;
  }
  .shadow{
    box-shadow:0px 0px 1px #646262
  }
  .custom-inp {
    outline:none;
    border:none;
    background:lightblue;
  }
 .custom-inp:focus{
  background:skyblue;
 }
 a{
   text-decoration: none;
   font-size:12px;
 }
 a:active{
   color:whitesmoke
 }
  </style>
  <!--- CSS --------->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>ESP8266</title>
  </head>
  <body class="d-flex justify-center align-center" >
    <div class="column">

  <div class="container row d-flex justify-center ">
  <form type="post" id="tokenres" class="column justify-center input-holder shadow">
  <p class="bold">Server Settings</p>
  <label for="tokentext" >Input token text</label>
  <input type="text" class="custom-inp" id="tokentext" value="" placeholder="Place token here" required>
  <a href="https://customaticparts.com/servicePortal/app/api/" target="_blank" class="mt-10" style="font-size: ">Get Token Here</a>
  <input type="submit" id="but1" class="mt-10" value="Update Token" name="click" ></input>
  </form>
  </div>
</div>


  <!--- JS --------->
  <script>
  window.addEventListener('load',(event)=>{
    let but1 = document.getElementById("but1");
    let tokenres = document.getElementById("tokenres");


      tokenres.addEventListener('submit',(e)=>{
        e.preventDefault();
        let input_data = document.getElementById("tokentext").value;

        setToken((dataResp)=>{
          console.log(dataResp.responseText);
          },input_data);
        })

    })
    const setToken = function(callback,token){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = () => {
        if(xhttp.readyState == 4 && xhttp.status == 200){
          callback(xhttp);
          }
        }
        xhttp.open("POST","./setToken",true);
        xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
        xhttp.send("token="+token);
    }
  </script>
  <!-- JS --------->
  </body>
</html>

)====";


return webpageCode;
}



//Wifi Settings
String wifiPage(IPAddress ip){
const char webpageCode[] = 
R"====(
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
  <!--- CSS --------->
  <style>
  .column {
    display:flex;
    flex-direction:column;
  }
  .row {
    display:flex;
    flex-direction:row;
  }
  .container{
    width:100%;
    height:100%;
  }
  input[type="button"], input[type="submit"],input[type="text"],input[type="password"]{
    min-width:100px;
    padding:5px;
  }
  .all-center{
    align-items:center;
    align-content:center;
    justify-content:center;
  }
  .align-center{
    align-items:center;
    align-content:center;
  }
  .justify-center{
    justify-content:center;
  }
  .input-holder{
    min-width:200px;
    min-height:200px;
    padding:10px;
    background-color:white;
  }
  body{
    min-height:90vh;
    background:whitesmoke
  }
  .d-flex{
    display:flex;
  }
  .inherit-h{
    height:inherit !important;
  }
  label{
    font-size:12px;
  }

  .mt-10{
    margin-top:10px;
  }

  :root{
    font-family:sans-serif;
  }
  .bold{
    font-weight:bold;
  }
  .shadow{
    box-shadow:0px 0px 1px #646262
  }
  .custom-inp {
    outline:none;
    border:none;
    background:lightblue;
  }
 .custom-inp:focus{
  background:skyblue;
 }
 a{
   text-decoration: none;
   font-size:12px;
 }
 a:active{
   color:whitesmoke
 }
  </style>
  <!--- CSS --------->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>ESP8266</title>
  </head>
  <body class="d-flex justify-center align-center" >
    <div class="column">
  <div class="container row d-flex justify-center ">
  <form type="post" id="wifires" class="column justify-center input-holder shadow" >
  <p class="bold">Server Settings</p>
  <label for="wiuser">Input Wifi SSID/Name</label>
  <input type="text" class="custom-inp" id="wiuser" value="" placeholder="Wifi Name" required >
  <label for="wipass" class="mt-10">Input Wifi Password</label>
  <input type="password" class="custom-inp" id="wipass" value="" placeholder="Wifi password" required >
  <input type="submit" id="but1" class="mt-10" value="Update Wifi" ></input>
  </form>
  </div>
</div>
  <!--- JS --------->
  <script>
  window.addEventListener('load',(event)=>{
    let but1 = document.getElementById("but1");
    let wifires = document.getElementById("wifires");
      wifires.addEventListener('submit',(e)=>{
        e.preventDefault();
        let input_data = document.getElementById("wiuser");
        let input_pass = document.getElementById("wipass");
        input_data.disabled = true;
        input_pass.disabled = true;
        setWifi((dataResp)=>{
                 var data = JSON.parse(dataResp.responseText)
                 if(data["success"]){
                  alert("Server successfully connected to wifi --- Server New IP : " + data["ip_address"]);
                 }
                 else{
                   alert("Server fail to Connect into wifi --- Please try again.");
                 }
                  window.location.reload();
               },input_data.value,input_pass.value);

    })
  })
    const setWifi = function(callback,user,pass){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = () => {
        if(xhttp.readyState == 4 && xhttp.status == 200){
          callback(xhttp);
          }  }
        xhttp.open("POST","./setWifi",true);
        xhttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
        xhttp.send("user="+user+"&pass="+pass);
    }
  </script>
  <!-- JS --------->
  </body>
</html>

)====";


return webpageCode;
}
