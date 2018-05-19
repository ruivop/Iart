var playing = true;
var turn = 1;
var times = 0;
var fistMove = [];
var secondMove = [];
var validMoves = [];
var mode = "pvp";//pvp || pvc || cvp || cvc
var depth = 2;

var boardinit = [
    [0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0],
    [0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2],
    [2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0],
    [0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0],
    [0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0]
];

var boardarr = [
    [0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0],
    [0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2],
    [2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0],
    [0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0],
    [0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0]
];

var coulorBacks = "black";
var coulorWhites = "white";
var emptyColour = "#eb9850";
var coulourCanSeletect = "#E78631";

var boardSize = 14;

function createBoard() {
    var board = document.getElementById("board");

    var row = document.createElement("tr");
    for (var j = 0; j < boardSize + 1; j++) {
        var cell = document.createElement("td");
        cell.classList.add("numberAnotation");
        if (j != 0)
            cell.innerHTML = j - 1;
        row.appendChild(cell);
    }
    board.appendChild(row);

    var id = 0;
    for (var i = 0; i < boardSize; i++) {
        var row = document.createElement("tr");
        for (var j = 0; j < boardSize + 1; j++) {
            var cell = document.createElement("td");
            if (j == 0) {
                cell.innerHTML = i;
                cell.classList.add("numberAnotation");
            } else {
                cell.id = id++;
                cell.innerHTML = "";
                cell.classList.add("playCell");
                cell.onmouseover = function(event) {
                    var i = parseInt(event.target.id / boardSize);
                    var j = event.target.id % boardSize;
                    if (canplay(i, j))
                        event.target.style.backgroundColor = turn == 1 ? coulorBacks : coulorWhites;
                };
                cell.onmouseout = function(event) {
                    var i = parseInt(event.target.id / boardSize);
                    var j = event.target.id % boardSize;
                    if (canplay(i, j))
                        event.target.style.backgroundColor = coulourCanSeletect;
                };
                cell.onclick = function(event) {
					if(!playing)
						return;
                    var i = parseInt(event.target.id / boardSize);
                    var j = event.target.id % boardSize;

                    if (canplay(i, j)) {
                        boardarr[i][j] = turn;
                        if (times == 1) {
                            var playingIn = document.getElementById("playingIn");
                            playingIn.innerHTML = fistMove[0] + " - " + fistMove[1] + " and " + parseInt(i) + " - " + parseInt(j);
                            secondMove[0] = i;
                            secondMove[1] = j;
                            //turn = (turn % 2) + 1;
                            times = 0;
							checkEndGame();
                            //createvalidMoves();
                        } else {
                            fistMove[0] = i;
                            fistMove[1] = j;
                            times = 1;
                        }
                    }
                    drawBoard();
                };
            }
            row.appendChild(cell);
        }
        board.appendChild(row);
    }
    drawBoard();
	
	$('#newGame').on('click', createNewGame);
	
	$('#modeSelector').change(function(){
        mode = $(this).find("option:selected").attr('value');
		if(mode != "pvp")
			document.getElementById("minimaxHaeadSelector").style.display = "block";
		else
			document.getElementById("minimaxHaeadSelector").style.display = "none";
		playBlacks();
    });
	
	$('#minimaxHaeadSelector').change(function(){
        depth = parseInt($(this).find("option:selected").attr('value'));
    });
}


function canplay(i, j) {
  if(boardarr[i][j] ==0)
    if (times == 0 && isInFirstMoves(i, j))
        return true;
    else if (times == 1 && isInSecondMoves(i, j))
        return true;
    return false;
}

function isDiagnonalyAdj(i, j, colour) {
    if (i + 1 < boardSize && j + 1 < boardSize && boardarr[i + 1][j + 1] == colour && boardarr[i + 1][j] != colour && boardarr[i][j + 1] != colour)
        return true;
    if (i + 1 < boardSize && j - 1 >= 0 && boardarr[i + 1][j - 1] == colour && boardarr[i + 1][j] != colour && boardarr[i][j - 1] != colour)
        return true;
    if (i - 1 >= 0 && j - 1 >= 0 && boardarr[i - 1][j - 1] == colour && boardarr[i - 1][j] != colour && boardarr[i][j - 1] != colour)
        return true;
    if (i - 1 >= 0 && j + 1 < boardSize && boardarr[i - 1][j + 1] == colour && boardarr[i - 1][j] != colour && boardarr[i][j + 1] != colour)
        return true;
    return false;
}

function drawBoard() {
    for (var i = 0; i < boardarr.length; i++) {
        for (var j = 0; j < boardarr.length; j++) {
            var playingIn = document.getElementById(i * boardarr.length + j);
            if (boardarr[i][j] == 1)
                playingIn.style.backgroundColor = coulorBacks;
            else if (boardarr[i][j] == 2)
                playingIn.style.backgroundColor = coulorWhites;
            else if (canplay(i, j)) {
                playingIn.style.backgroundColor = coulourCanSeletect;
            } else
                playingIn.style.backgroundColor = emptyColour;
        }
    }
    document.getElementById("turnplay").innerHTML = turn == 1 ? "Playing Blacks" : "Playing Whites";
}

function createvalidMoves() {
    validMoves.splice(0, validMoves.length);
    for (var i1 = 0; i1 < boardarr.length; i1++) {
        for (var j1 = 0; j1 < boardarr.length; j1++) {
            if (boardarr[i1][j1] == 0) {
                boardarr[i1][j1] = turn;
                for (var i2 = 0; i2 < boardarr.length; i2++) {
                    for (var j2 = 0; j2 < boardarr.length; j2++) {
                      if(boardarr[i2][j2] == 0){
                        boardarr[i2][j2] = turn;
                        if (!isDiagnonalyAdj(i1, j1, turn) && !isDiagnonalyAdj(i2, j2, turn)) {
                            validMoves.push([i1, j1, i2, j2]);
                            validMoves.push([i2, j2, i1, j1]);
                        }
                        boardarr[i2][j2] = 0;
                      }
                    }
                }
                boardarr[i1][j1] = 0;
            }
        }
    }
}

function isInFirstMoves(is, js) {
    for (var i = 0; i < validMoves.length; i++) {
        if (is == validMoves[i][0] && js == validMoves[i][1])
            return true;
    }
    return false;
}

function isInSecondMoves(is, js) {
  for (var i = 0; i < validMoves.length; i++) {
      if (validMoves[i][0] == fistMove[0] && validMoves[i][1] == fistMove[1] &&
          is == validMoves[i][2] && js == validMoves[i][3])
          return true;
  }
  return false;
}
createvalidMoves();
document.onload = createBoard();


function createCORSRequest(method, url) {
  var xhr = new XMLHttpRequest();
  if ("withCredentials" in xhr) {
    // XHR for Chrome/Firefox/Opera/Safari.
    xhr.open(method, url, true);
  } else if (typeof XDomainRequest != "undefined") {
    // XDomainRequest for IE.
    xhr = new XDomainRequest();
    xhr.open(method, url);
  } else {
    // CORS not supported.
    xhr = null;
  }
  return xhr;
}

function sendRequest(jsonSend){
  var xmlhttp = new createCORSRequest("PUT", "http://localhost:34568");
  xmlhttp.setRequestHeader("Content-Type", "application/json");

  xmlhttp.onload = function() {
    var responseText = xmlhttp.responseText;
    var resp = JSON.parse(responseText);
	if(resp.Response == "has_won"){
		if(resp.Value) {
		//make a new array
		
		document.getElementById("turnplay").innerHTML = "Game Won by " + (turn == 2 ? "Whites" : "Blacks");
		document.getElementById("info").innerHTML = "To start a new game (whith blacks) click in the button";
		playing = false;
		} else {
			turn = (turn % 2) + 1;
			if(turn == 1)
				playBlacks();
			else
				playWites();
            createvalidMoves();
		}
	} else {
		console.log(resp);
		fistMove[0]=resp.i1;
		fistMove[1]=resp.j1;
		secondMove[0]=resp.i2;
        secondMove[1]=resp.j2;
		document.getElementById("playingIn").innerHTML = fistMove[0] + " - " + fistMove[1] + " and " + parseInt(secondMove[0]) + " - " + parseInt(secondMove[1]);        
		boardarr[resp.i1][resp.j1] = turn;
		boardarr[resp.i2][resp.j2] = turn;
		checkEndGame();
		drawBoard();
	}
	
   };
   xmlhttp.onerror = function() {
     console.log('There was an error!');
   };
  xmlhttp.send(JSON.stringify(jsonSend));
}

function checkEndGame(){
	var jsonSend = {Request:"has_won", Board:boardarr};
	sendRequest(jsonSend);
}

function pc_play(color){
	var jsonSend = {Request:"pc_play", Board:boardarr, player:color, depth:depth};
	sendRequest(jsonSend);
}
 
 function createNewGame(){
	for (var i = 0; i < boardinit.length; i++)
		boardarr[i] = boardinit[i].slice();
	turn = 1;
	times = 0;
	playing = true;
	createvalidMoves();
	document.getElementById("playingIn").innerHTML = "";
	document.getElementById("info").innerHTML = "Click in the tiles to place a piece";
	drawBoard();
 }
 
function playBlacks(){
	playing = false;
	if(mode == "pvp"){
		playing = true;
	}
	if(mode == "pvc"){
		playing = true;
	}
	if(mode == "cvp"){
		var playingIn = document.getElementById("playingIn");
        playingIn.innerHTML = "Wating for computer to play";
		pc_play(1);
	}
	if(mode == "cvc"){
		var playingIn = document.getElementById("playingIn");
        playingIn.innerHTML = "Wating for computer to play";
		pc_play(1);
	}
}

function playWites(){
	playing = false;
	if(mode == "pvp"){
		playing = true;
	}
	if(mode == "pvc"){
		var playingIn = document.getElementById("playingIn");
        playingIn.innerHTML = "Wating for computer to play";
		pc_play(2);
	}
	if(mode == "cvp"){
		playing = true;
	}
	if(mode == "cvc"){
		var playingIn = document.getElementById("playingIn");
        playingIn.innerHTML = "Wating for computer to play";
		pc_play(2);
	}
}