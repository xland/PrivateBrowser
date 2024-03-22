// #region 标题栏 
(()=>{
    // let domTitle  = document.querySelector(".title");
    // domTitle.addEventListener("mousedown",(evt)=>{
    //     chrome.webview.hostObjects.sync.host.MouseDownDrag();
    //     evt.preventDefault();
    //     evt.stopPropagation();
    // })
    document.addEventListener("mousedown",(evt)=>{
        if(evt.x>0&&evt.y>0&&evt.x<6&&evt.y<6){
            // document.body.style = "cursor:nw-resize;"
            chrome.webview.hostObjects.sync.host.HitTest(13);//HTTOPLEFT
        }else{
            // document.body.style = ""
        }
        
        
        evt.preventDefault();
        evt.stopPropagation();
    })
    let minimizeBtn = document.querySelector(".minimizeBtn")
    minimizeBtn.addEventListener("click",()=>{
        chrome.webview.hostObjects.sync.host.Close();
        evt.preventDefault();
        evt.stopPropagation();
    })
})()
// #endregion
