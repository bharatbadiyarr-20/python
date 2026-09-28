let button = document.querySelectorAll(".non-screen .button-line button");
let display = document.querySelector(".screen");

function updatedisplay(val){
    if(val=="sin" || val=="cos" || val=="tan" || val=="cot" || val=="sec" || val=="cosec"){
        display.innerText += val + "(";
        return;
    }
    display.innerText += val;
}
function calculation(){
    try{
    let expr=display.innerText;
     expr=expr.replace(/π/g,Math.PI);
    expr = expr.replace(/sin/g, "Math.sin");
    expr = expr.replace(/cos/g, "Math.cos");
    expr = expr.replace(/tan/g, "Math.tan");
    expr = expr.replace(/log/g, "Math.log10");
    expr = expr.replace(/ln/g, "Math.log");
    expr = expr.replace(/√/g, "Math.sqrt");
    let result=eval(expr);
    display.innerText=result;
    }
    catch(e){
        display.innerText="Error";
    }

}
button.forEach(btn => {
    btn.addEventListener("click", ()=>{
       let val= btn.innerText.trim();
        if(val === "="){
            calculation();
            return;
        }
        if(val=="del"){
            let expr=display.innerText;
            display.innerText = expr.slice(0, -1);
            return;
        }
        if(val=="AC"){
            display.innerText="";
            return;
        }
         updatedisplay(val);
    });
});

