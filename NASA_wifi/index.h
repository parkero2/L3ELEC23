const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Oliver's mars rover</title>
    <style>
        /*Add styles*/
        .slider {
            transform: rotate(-90deg);
            margin-top: 80px;
        }
        #controls {
            margin: auto;
            width: fit-content;
            height: 200px;
            border: 1px;
            border-style: solid;
        }
        p {
            margin: auto;
            width: fit-content;
        }
        h1 {
            margin: auto;
            width: fit-content;
            margin-top: 50px;
        }
        #resetL {
            margin: auto;
            width: fit-content;
            margin-left:45px;
        }
        #resetR {
            margin: auto;
            width: fit-content;
            margin-left:85px;
        }
        body {
            background-color: #000000;
            color: #ffffff;
        }
    </style>
</head>
<body>
    <h1>Oliver's mars rover</h1>
    <br>
    <br>
    <div id="controls">
        <input type="range" min="-255" max="255" value="0" class="slider" id="left">
        <input type="range" min="-255" max="255" value="0" class="slider" id="right">
        <p>left/right</p>
        <div id="current">
            <p id="leftinfo">Left: 0</p>
            <p id="rightinfo">Right: 0</p>
        </div>
        <button id="resetL">reset</button>
        <button id="resetR">reset</button>
    </div>
</body>

<script>
    const POSTURL = "./post";

    //Grab the elements that will be used as the input
    let lft = document.getElementById("left");
    let rgt = document.getElementById("right");
    let resetL = document.getElementById("resetL");
    let resetR = document.getElementById("resetR");
    let leftinfo = document.getElementById("leftinfo");
    let rightinfo = document.getElementById("rightinfo");
    
    //Add reset buttons functionality 
    resetL.addEventListener("click", function() {
        lft.value = 0;
        fetch(POSTURL + "?lft=" + 0, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            }}).then();
    });
    resetR.addEventListener("click", function() {
        rgt.value = 0;
        fetch(POSTURL + "?rgt=" + 0, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            }}).then();
    });
    //Add event listeners to the inputs
    lft.addEventListener("input", function() {
        leftinfo.innerHTML = "Left: " + lft.value;
        //Send the value of the input to the server
        fetch(POSTURL + "?lft=" + lft.value, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            }}).then();
    });
    rgt.addEventListener("input", function() {
        rightinfo.innerHTML = "Right: " + rgt.value;
        //Send the value of the input to the server
        let req = fetch(POSTURL + "?rgt=" + rgt.value, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            }}).then();
    });
</script>
</html>


)=====";