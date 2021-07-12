
//webpagecode
String pageData(IPAddress ip){
const char webpageCode[] = 
R"====(
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
  <!---------- CSS --------->
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
  input[type="button"], input[type="submit"],input[type="text"]{
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
    border: 1px solid seagreen;
    border-radius: 10px;
    background-color:white;
  }
  body{
    min-height:100vh;
    background-color:lightblue;
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
  bold{
    font-weight:bold;
  }

  .custom-inp {
    outline:none;
    border:none;
    background:lightblue;
  }

 .custom-inp:focus{
  background:skyblue;
 }

  </style>
  <!---------- CSS --------->

    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <title>ESP8266</title>
  </head>
  <body >
  <div class="container d-flex justify-center">
  <form type="post" id="tokenres" class="column justify-center input-holder "> 
  <p class="bold">ESP8266 Settings</p>
  <label for="but1">Input token text</label>
  <input type="text" class="custom-inp" id="tokentext" value="" placeholder="Place token here" required>
  <input type="submit" id="but1" class="mt-10" value="Update Token" name="click" ></input>
  </form>
  </div>
  
  <!---------- JS --------->
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
  <!---------- JS --------->

  </body>
</html>)====";


return webpageCode;
}
