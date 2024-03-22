let fs = require("fs-extra")
let path = require("path")
const { JSDOM } = require("jsdom");
const { minify } = require('html-minifier-terser');
let srcPath = './src'
// let changeName = (str) => {
//     let result = ""
//     for(let i=0;i<str.length;i++){
//         if(str[i] === ".") break;
//         if(str.charCodeAt(i) >= 65 && str.charCodeAt(i) <= 90){
//             result += "-"+str[i].toLowerCase();
//         }else{
//             result +=str[i];
//         }
//     }
//     if(result.startsWith("-")) result = result.substring(1);
//     return result;
// }
let start = async ()=>{
    let jsContent = "";
    let fileNames = fs.readdirSync(srcPath);
    for(let fileName of fileNames){
        if(fileName.startsWith("index")) continue;
        // let name = changeName(fileName);
        // console.log(name);
        let content = fs.readFileSync(path.join(srcPath,fileName)).toString();
        const dom = new JSDOM(content);
        let html = dom.window.document.querySelector("template").innerHTML;
        html = await minify(html,{removeComments: true,collapseWhitespace:true,minifyCSS:true});
        // console.log(html);
        let js = dom.window.document.querySelector("script").innerHTML;
        js = await minify(js,{removeComments: true,collapseWhitespace:true,minifyJS:true});
        js = js.replace(`%TEMPLATE_CONTENT%`,html)+"\r\n";
        jsContent += js;
    }
    fs.writeFileSync(path.join(srcPath,"index.js"),jsContent);
}
start();