import QtQuick 2.0


Component {
    id: listDelegate
    Item  {        
        property variant feedData: model

        Component.onCompleted: {
            container.listItem = feedData
            container.listItemClicked("First");
        }

        height:82
        width:292
        Row {
            Column {
                Rectangle {
                        id: blackRect
                        height:80
                        width:290
                        color: "transparent"
                        border.color: "green"
                        border.width:1
                        Text {
                            x: 9
                            y: 8
                            width: 0
                            height: 0
                            anchors.fill: parent;
                            text: '<html><style type="text/css"> a:link {color:green} a:active { color:lime } </style>'
                                 + '<a href="'+url+'"><b>'+title + "</b></a> "
                                  + '<br /><br/><span style="color:black"><b>'+postedAgo+' '+ points + ' points ' + commentCount +' <a href="'+commentsUrl+'">comments</a></b></html>';
                            textFormat: Text.RichText
                            anchors.leftMargin: 9
                            anchors.topMargin: 8
                            anchors.rightMargin: -9
                            anchors.bottomMargin: -8
                            wrapMode: Text.WordWrap
                            onLinkActivated: {
                                if(link==feedData.commentsUrl) {
                                    console.log(feedData.commentsUrl);
                                    container.listItemCommentsLinkClicked(commentsUrl);
                                    articleList.currentIndex = index
                                }
                                else {
                                    container.listItem = feedData
                                    container.listItemClicked("");
                                    articleList.currentIndex = index
                                }
                            }
                        }
//                        MouseArea {
//                               hoverEnabled: false
//                               anchors.fill: parent;
//                               onClicked: {
//                                   container.listItem = feedData
//                                   container.listItemClicked("");
//                                   articleList.currentIndex = index
//                               }
//                        }
                    }
              }
         }
    }
}

