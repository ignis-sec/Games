
																		
var canvas= document.getElementById('mainCanvas')						//variables
var context= canvas.getContext('2d');
var key=83;
var keylast=83;
var SnakeLength=4;
var applex=getRandomInt(0,20);
var appley=getRandomInt(0,20);
var dif=1;
var score=0;
var highScore = JSON.parse(localStorage.getItem('highScore'));
var curLevel=0;
var dummy = [0,0,0,0,0,0,0];

var level= 
[
	[
	[1,0],[500,0]
	],

	[
		[60,0], [0,0] , [1,0] ,[2,0] ,[3,0] ,[4,0] ,[5,0] ,[6,0] ,[7,0] ,[8,0] ,[9,0] ,[10,0] ,[11,0] ,[12,0] ,[13,0] ,[14,0] ,[15,0] ,[16,0] ,[17,0] ,[18,0] ,[19,0], [20,0] ,[21,0] ,[22,0] ,[23,0] ,[24,0] ,[25,0] ,[26,0] ,[27,0] ,[28,0] ,[29,0],[0,24] , 
		[1,24] ,[2,24] ,[3,24] ,[4,24] ,[5,24] ,[6,24] ,[7,24] ,[8,24] ,[9,24] ,[10,24] ,[11,24] ,[12,24] ,[13,24] ,[14,24] ,[15,24] ,[16,24] ,[17,24] ,[18,24] ,[19,24], [20,24] ,[21,24] ,[22,24] ,[23,24] ,[24,24] ,[25,24] ,[26,24] ,[27,24] ,[28,24] ,[29,24],[30,24]
	],

	[
		[107,0], [0,0] , [1,0] ,[2,0] ,[3,0] ,[4,0] ,[5,0] ,[6,0] ,[7,0] ,[8,0] ,[9,0] ,[10,0] ,[11,0] ,[12,0] ,[13,0] ,[14,0] ,[15,0] ,[16,0] ,[17,0] ,[18,0] ,[19,0], [20,0] ,[21,0] ,[22,0] ,[23,0] ,[24,0] ,[25,0] ,[26,0] ,[27,0] ,[28,0] ,[29,0],[0,24] , 
		[1,24] ,[2,24] ,[3,24] ,[4,24] ,[5,24] ,[6,24] ,[7,24] ,[8,24] ,[9,24] ,[10,24] ,[11,24] ,[12,24] ,[13,24] ,[14,24] ,[15,24] ,[16,24] ,[17,24] ,[18,24] ,[19,24], [20,24] ,[21,24] ,[22,24] ,[23,24] ,[24,24] ,[25,24] ,[26,24] ,[27,24] ,[28,24] ,[29,24],[30,24],
		[0,1], [0,2], [0,3], [0,4], [0,5], [0,6], [0,7], [0,8], [0,9], [0,10], [0,11], [0,12], [0,13], [0,14], [0,15], [0,16], [0,17], [0,18], [0,19], [0,20], [0,21], [0,22], [0,23],
		[29,1], [29,2], [29,3], [29,4], [29,5], [29,6], [29,7], [29,8], [29,9], [29,10], [29,11], [29,12], [29,13], [29,14], [29,15], [29,16], [29,17], [29,18], [29,19], [29,20], [29,21], [29,22], [29,23],[30,23]
	]
]


var levelLength=level[curLevel][0][0];



document.addEventListener("keypress", keyPressHandler,false);			//listener

//////////////////////////////////////////////////////////////////////////
window.onload = function()												//what to do at start
{
	updateDifficulty();			
	updateHscore();
	updateLevel();
	document.querySelector('.results').innerHTML = score; 
	draw();
}

//////////////////////////////////////////////////////////////////////////
function keyPressHandler(e)                                             //key handler
{	
	key=e.keyCode;														
	if(keylast==key+4||keylast==key-4||keylast==key+3||keylast==key-3)	//if its the opposite of current direction, disregard keypress
	{
		key=keylast;
	}	
}
	var x =[480,480,480,480];											//initial snake
	var y =[64,96,128,160];

//////////////////////////////////////////////////////////////////////////
function draw()															//main function
{
	context.clearRect(0,0,canvas.width,canvas.height);
	checkCollision();
	drawApple();
	drawlevel();
	for(i=SnakeLength-1;i>=0;i--)
	{
		if(i!=SnakeLength-1)
		{
			handlePushBack();
		}
		drawSnake();
	}
	handleMovement();
	window.setTimeout(draw,dif*25);										//loop element
}

//////////////////////////////////////////////////////////////////////////
function handleMovement()												//check which key was pressed and which way should the snake go next tick
{
	if(key==87||key==119)
		{
			y[0]-=32;
			y[0]=(canvas.height+y[0])%canvas.height;
		}else if(key==65||key==97)
		{
			x[0]+=-32;
			x[0]=(x[0]+canvas.width)%canvas.width;
		}else if(key==83||key==115)
		{
			y[0]+=32;
			y[0]=y[0]%canvas.height;
		}else if(key==68||key==100)
		{
			x[0]+=32;
			x[0]=x[0]%canvas.width;
	}	
	keylast=key;
}

//////////////////////////////////////////////////////////////////////////
function handlePushBack()												//move every element of array 1 block behind
{
	x[i+1]=x[i];
	y[i+1]=y[i];
}

//////////////////////////////////////////////////////////////////////////
function drawSnake()													//draw the rectangle
{
	context.beginPath();
	context.rect(x[i],y[i],30,30);
	context.fillStyle = "#0095DD";
	context.fill(); 
	context.closePath();
}

//////////////////////////////////////////////////////////////////////////						
function checkCollision()												//collision engine
{	
	if(x[0]==applex*32&&y[0]==appley*32)								//if it is an apple
	{	
		spawnApple();
		SnakeLength++;
		updateScore();
		updateHscore();
	}
	for(j=1;j<SnakeLength-1;j++)										//if it is itself
	{
		if(x[0]==x[j] && y[0]==y[j])
		{
			if(SnakeLength>4)
			{
					alert("Game over");

				restartLevel();
			}		
		}
	}
	for(m=1;m<=levelLength;m++)											//if its block
	{
		if(x[0]==level[curLevel][m][0]*32 && y[0]==level[curLevel][m][1]*32)
		{
				alert("Game over");

			restartLevel();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
function spawnApple()													//spawn apple at random
{
	applex=getRandomInt(0,20);
	appley=getRandomInt(0,20);	

	for(n=1;n<=levelLength;n++)
	{
		if(applex==level[curLevel][n][0]*32 && appley==level[curLevel][n][1]*32)
		{
				spawnApple();
		}
	}

}

//////////////////////////////////////////////////////////////////////////
function drawApple()													//draw the apple every tick
{
	context.beginPath();
	context.rect(applex*32,appley*32,30,30);
	context.fillStyle = "red";
	context.fill(); 
	context.closePath();
}

//////////////////////////////////////////////////////////////////////////																								
function getRandomInt(min, max) 										//get random int 
{	
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive
}

//////////////////////////////////////////////////////////////////////////
function updateScore()													//update scoreboard
{
	score=score + (11-dif)*5
	document.querySelector('.results').innerHTML = score;
}

//////////////////////////////////////////////////////////////////////////
function updateDifficulty()												//update game speed
{
	document.querySelector('.Leveldif').innerHTML = (11-dif)*100;
}

//////////////////////////////////////////////////////////////////////////
function updateHscore()													//update high score
{
	if (score > highScore[curLevel])
	{
		 highScore[curLevel] = score;
		 localStorage.setItem('highScore', JSON.stringify(highScore));
	}
	document.querySelector('.hscore').innerHTML =highScore[curLevel];
}

//////////////////////////////////////////////////////////////////////////
function increase()														//increase game speed(decrease the time interval)
{
	if(dif>1)
	dif--;
	updateDifficulty();
}

//////////////////////////////////////////////////////////////////////////
function decrease()														//opposite of above
{
	if(dif<10)
	dif++;
	updateDifficulty();
}

//////////////////////////////////////////////////////////////////////////
function drawlevel()
{

	for(k=1;k<=levelLength;k++)
	{
		drawBlock(level[curLevel][k][0]*32,level[curLevel][k][1]*32);
	}


}

//////////////////////////////////////////////////////////////////////////
function drawBlock(x,y)
{
	context.beginPath();
	context.rect(x,y,30,30);
	context.fillStyle = "black";
	context.fill(); 
	context.closePath();
}

//////////////////////////////////////////////////////////////////////////
function lincrease()														//increase game speed(decrease the time interval)
{
	if(curLevel<100)
	restartLevel();
	curLevel++;
	updateLevel();

}

//////////////////////////////////////////////////////////////////////////
function ldecrease()														//opposite of above
{
	if(curLevel>0)
	
	curLevel--;
	updateLevel();
	restartLevel();
}

//////////////////////////////////////////////////////////////////////////
function updateLevel()												//update game speed
{
	levelLength=level[curLevel][0][0];
	document.querySelector('.levelhtml').innerHTML = curLevel;
	document.querySelector('.hscore').innerHTML =highScore[curLevel];
}

//////////////////////////////////////////////////////////////////////////
function restartLevel()
{
	x =[480,480,480,480];											//initial snake
	y =[64,96,128,160];
	SnakeLength=4;
	key=83;	
	score=0;
	updateScore();
	updateHscore();

}


