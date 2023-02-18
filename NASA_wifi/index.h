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
            margin-left:40px;
        }
        #resetR {
            margin: auto;
            width: fit-content;
            margin-left:90px;
        }
        body {
            background-color: #000000;
            color: #ffffff;
        }
    </style>
    </script>
</head>
<body>
    <h1>Oliver's mars rover</h1>
    <br>
    <br>
    <div id="controls">
        <input type="range" min="-255" max="255" value="0" class="slider" id="left">
        <input type="range" min="-255" max="255" value="0" class="slider" id="right">
        <p>left/right</p>
        <br><br>
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
    
    //Add reset buttons functionality 
    resetL.addEventListener("click", function() {
        lft.value = 0;
    });
    resetR.addEventListener("click", function() {
        rgt.value = 0;
    });
    //Add event listeners to the inputs
    lft.addEventListener("input", function() {
        //Send the value of the input to the server
        fetch(POSTURL, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                left: lft.value
            })
        }).then();
    });
    rgt.addEventListener("input", function() {
        //Send the value of the input to the server
        let req = fetch(POSTURL, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                right: rgt.value
            })
        }).then();
    });
</script>
</html>
)=====";