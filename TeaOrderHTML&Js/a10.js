let tops = [];
let drinksArray = [];

let list = document.getElementById("div1");
let allTops = document.getElementsByName("toppings");
let radioSelected = document.getElementsByName("type");
let wantMilk = document.getElementById("selectOption");
let table = document.getElementById("tbl1");

let teaData = [ ['Black', 2.0] , ['Green', 2.50] , ['Red', 3.00] ];
let toppingsData = [ ['Pearls', 0.25] , ['Mango Stars', 1.00] , ['Grass Jelly', 0.50] ,['Coconut Jelly', 0.75]  ];

addTop.onclick = addToppings;
removeTop.onclick = removeToppings;
addDrink.onclick = addIt;
removeDrink.onclick = removeIt;
emptyOrder.onclick = finish;



function displayToppings(){

	let display = "<ul>"

	for(let i = 0; i < tops.length; i++){
		display+= "<li>" + tops[i] + "</li>";
	}

	display += "</ul>"

	list.innerHTML = display;

}


function addToppings(){


	tops = [];

	for(let i = 0; i < allTops.length; i++){
		if(allTops[i].checked){
			tops.push(allTops[i].value);
		}
	}

	displayToppings();


}



function removeToppings(){
	tops.pop();
	displayToppings();
}



function TeaDrink(type, drinkToppings, milk){
	this.type = type;
	this.drinkToppings = drinkToppings.slice();
	this.milk = milk;

}


function calculateCost(obj){

	let cost = 0;

	for(let i = 0; i < teaData.length; i++){
		if(obj.type == teaData[i][0]){
			cost += teaData[i][1];
		}
	}

	for(let i = 0; i < obj.drinkToppings.length; i++){

		for(let j = 0; j < toppingsData.length; j++){
			if(obj.drinkToppings[i] == toppingsData[j][0]){
				cost += toppingsData[j][1];
			}
		}
		
	}

	if(obj.milk == 'Yes'){
		cost += 1.00;
	}

	return cost;

}


function createTable(){

	        table.innerHTML = "";
	
		    let newRow = table.insertRow(0);
			let newColumn = newRow.insertCell(0);
			newColumn.appendChild(document.createTextNode("Tea"));
			newColumn = newRow.insertCell(1);
			newColumn.appendChild(document.createTextNode("Milk"));
			newColumn = newRow.insertCell(2);
			newColumn.appendChild(document.createTextNode("Toppings"));
			newColumn = newRow.insertCell(3);
			newColumn.appendChild(document.createTextNode("Cost"));

			
}




function addIt(){

	let type, drinkToppings ,milk;

	for(let i = 0; i < radioSelected.length; i++){
		if(radioSelected[i].checked){
			type = radioSelected[i].value;
		}
	}

	drinkToppings = tops.slice();

	let milkValue = wantMilk.value;

	drinksArray.push(new TeaDrink(type, drinkToppings, milkValue));

	if(drinksArray.length == 1){
		createTable();
	}

	let len = drinksArray.length;

	let newRow = table.insertRow(-1);
	let newColumn = newRow.insertCell(0);
	newColumn.appendChild(document.createTextNode(drinksArray[len - 1].type));
	newColumn = newRow.insertCell(1);
	newColumn.appendChild(document.createTextNode(drinksArray[len - 1].milk));
	newColumn = newRow.insertCell(2);
	newColumn.appendChild(document.createTextNode(drinksArray[len - 1].drinkToppings));
	newColumn = newRow.insertCell(3);
	newColumn.appendChild(document.createTextNode(calculateCost(drinksArray[len - 1])));

	
}

function removeIt(){


	if(drinksArray.length >= 1){
		drinksArray.pop();
		table.deleteRow(table.rows.length - 1);
	}

	if(drinksArray == 0){
		table.innerHTML = "";
	}

	
}


function finish(){
	table.innerHTML = "";
	while(drinksArray.length > 0){
		drinksArray.pop();
	}
}

















