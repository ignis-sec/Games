
																		
var canvas= document.getElementById('mainCanvas')						//variables
var context= canvas.getContext('2d');
var key=83;
var keylast=83;
var SnakeLength=4;
var applex=getRandomInt(0,20);
var appley=getRandomInt(0,20);



document.addEventListener("keypress", keyPressHandler,false);

function keyPressHandler(e)                                              //key handler
{
	
	key=e.keyCode;														
	if(keylast==key+4||keylast==key-4||keylast==key+3||keylast==key-3)	//if its the opposite of current direction, disregard keypress
	{
		key=keylast;
	}
	
}


setInterval(draw,100);													//game difficulty for future, interval time

	var x =[320,320,320,320];
	var y =[0,32,64,96];



function draw()															//main function
{
	context.clearRect(0,0,canvas.width,canvas.height);
	checkCollision();
	drawApple();
	
	for(i=SnakeLength-1;i>=0;i--)
	{
		if(i!=SnakeLength-1)
		{
			handlePushBack();
		}
		
		drawSnake();
	}
	handleMovement();
	
}

function handleMovement()												//check which key was pressed and which way should the snake go next tick
{
	if(key==87||key==119)
		{
			y[0]-=32;
			y[0]=(640+y[0])%640;
		}else if(key==65||key==97)
		{
			x[0]+=-32;
			x[0]=(x[0]+640)%640;
		}else if(key==83||key==115)
		{
			y[0]+=32;
			y[0]=y[0]%640;
		}else if(key==68||key==100)
		{
			x[0]+=32;
			x[0]=x[0]%640;
	}	
	keylast=key;
}

function handlePushBack()												//move every element of array 1 block behind
{
	x[i+1]=x[i];
	y[i+1]=y[i];
}

function drawSnake()													//draw the rectangle
{
		context.beginPath();
		context.rect(x[i],y[i],30,30);
		context.fillStyle = "#0095DD";
		context.fill(); 
		context.closePath();

}
						
function checkCollision()												//collision engine
{
	if(x[0]==applex*32&&y[0]==appley*32)
		{
			spawnApple();
			SnakeLength++;
		}
	for(j=1;j<SnakeLength-1;j++)
	{
		if(x[0]==x[j] && y[0]==y[j])
		{
			if(SnakeLength>4)
			{
			console.log(x[j]);
			console.log(x[0]);
			alert("Game over");
			x =[320,320,320,320];
			y =[0,32,64,96];
			SnakeLength=4;
			key=83;	
			}
				
		}
	}

}

function spawnApple()													//spawn apple at random
{
	applex=getRandomInt(0,20);
	appley=getRandomInt(0,20);		
}

function drawApple()													//draw the apple every tick
{
		context.beginPath();
		context.rect(applex*32,appley*32,30,30);
		context.fillStyle = "red";
		context.fill(); 
		context.closePath();

}
																								
function getRandomInt(min, max) 										//get random int 
{	
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive
}
