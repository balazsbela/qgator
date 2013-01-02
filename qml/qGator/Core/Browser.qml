import QtQuick 2.0
import QtWebKit 3.0

Rectangle {   
    id:browserContainer
    width: browser.width
    height: browser.height
    border.color: "green"
    border.width: 1
    WebView {
        id: webView
        anchors.fill:parent;
        url : navigationUrl
        onLoadingChanged : {
            console.log("LoadingChanged:"+loadRequest.status);
            switch(loadRequest.status) {
                case WebView.LoadStartedStatus : {
                        loadingImage.visible=true;
                        break;
                }
                case WebView.LoadSucceededStatus : {
                    loadingImage.visible=false;
                    break;
                }
                default :
                    loadingImage.visible=false;
            }
        }
    }
}
