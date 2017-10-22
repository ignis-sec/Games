var canvas= document.getElementById('mainCanvas')
var context= canvas.getContext('2d');
var key=83;
var SnakeLength=3;

document.addEventListener("keypress", keyPressHandler,false);

function keyPressHandler(e)
{
	
	key=e.keyCode;

}


setInterval(draw,1000);

	var x =,320,352];
	var y =[0,0,0];



function draw()
{
	context.clearRect(0,0,canvas.width,canvas.height);
	context.beginPath();
	handleMovement();
	for(i=0;i<SnakeLength;i++)
	{
		if(i!=SnakeLength-1)
		{
			handlePushBack();
		}
		
		drawSnake();
		
	}

}

function handleMovement()
{
	if(key==87||key==119)
		{
			y[0]-=32;
			y=(640+y[0])%640;
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
	console.log("moving");
}

function handlePushBack()
{
	x[i+1]=x[i];
	y[i+1]=y[i];
}

function drawSnake()
{
		context.rect(x[i],y[i],30,30);
		context.fillStyle = "#0095DD";
		context.fill(); 
		context.closePath();
		console.log("drawn");

}
