var canvas= document.getElementById('mainCanvas')
var context= canvas.getContext('2d');
var key=83;
var SnakeLength=5;

document.addEventListener("keypress", keyPressHandler,false);

function keyPressHandler(e)
{
	
	key=e.keyCode;

}


setInterval(draw,100);

	var x =[320,320,320,320,320];
	var y =[0,32,64,96,128];



function draw()
{
	context.clearRect(0,0,canvas.width,canvas.height);
	context.beginPath();
	handleMovement();
	for(i=SnakeLength-1;i>=0;i--)
	{
		if(i!=SnakeLength)
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
		console.log("drawn at");
		console.log(x[i]);
		console.log(y[i]);

}
