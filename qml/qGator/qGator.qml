import QtQuick 2.0
import "Core" 1.0 as Core
import "Core/loader.js" as Loader

Rectangle {
    property variant listItem
    signal listItemClicked(string meta)
    signal listItemCommentsLinkClicked(string commentsUrl)
    property string navigationUrl
    width: 1200
    height: 660
    id: container
    color: "#eee"  

    onListItemCommentsLinkClicked:{
        navigationUrl = commentsUrl
    }

    onListItemClicked:  {
        if(meta === "First") {
            if(navigationUrl === "") {
               navigationUrl = listItem.url
            }
        }
        else {
            navigationUrl = listItem.url
        }
    }

    Image {
        source: "Components/images/stripes.png";
        //source: "Components/images/graydient.jpg"
        fillMode: Image.Tile;
        anchors.fill: parent;
        opacity: 0.1
    }

    MouseArea {
        x: 0
        y: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent;
        onClicked: container.forceActiveFocus();
    }

    Text {
        id:title
        text: "Newsfeed"
        anchors.left: parent.left
        anchors.top:parent.top;
        anchors.topMargin: 10
        anchors.leftMargin: 10
        font.pixelSize:20; font.bold: true; color: "#5aa72d"; style: Text.Raised; styleColor: "black"
        opacity:1.0
    }

    Core.Input {
        id: searchField
        x: 215
        y: 10
        width: 179
        height: 24
    }

    Core.Button {
        id: updateButton
        x: 127
        y: 10
        width: 77
        height: 24
        label: "Update"
        buttonColor: "green"
        anchors.left: title.right
        anchors.leftMargin: 17
        anchors.topMargin: 10
        anchors.top: parent.top
        buttonHeight: 30
        buttonWidth: 70
        onButtonClick: {
            contentProvider.update();
        }
    }

    Core.Button {
        id: searchButton
        x: 798
        y: 10
        width: 77
        height: 24
        label: "Search"
        buttonColor: "green"
        anchors.left: searchField.right
        anchors.leftMargin: 9
        anchors.topMargin: 10
        anchors.top: parent.top
        buttonHeight: 30
        buttonWidth: 70
        onButtonClick: {
            contentProvider.retrieveSearchResults(searchField.text)
        }
    }

    Core.Button {
        id: saveButton
        x: 512
        y: 10
        width: 180
        height: 24
        label: "Save current article"
        buttonColor: "green"
        anchors.left: searchField.right
        anchors.leftMargin: 118
        anchors.topMargin: 10
        anchors.top: parent.top
        buttonHeight: 30
        buttonWidth: 70
        onButtonClick: {
            contentProvider.addToFavorites(articleList.currentIndex);
        }
    }

    Core.Button {
        id: removeFromFavorites
        x: 716
        y: 10
        width: 284
        height: 24
        label: "Remove current from favorites"
        buttonColor: "green"
        anchors.left: searchField.right
        anchors.leftMargin: 322
        anchors.topMargin: 10
        anchors.top: parent.top
        buttonHeight: 30
        buttonWidth: 70
        onButtonClick: {
            contentProvider.removeFromFavorites(articleList.currentIndex);
        }
    }

    Core.Button {
        id: favoritesButton
        x: 1034
        y: 10
        width: 135
        height: 24
        label: "Favorites"
        buttonColor: "green"
        anchors.left: searchField.right
        anchors.leftMargin: 640
        anchors.topMargin: 10
        anchors.top: parent.top
        buttonHeight: 30
        buttonWidth: 70
        onButtonClick: {
            contentProvider.loadFavorites();
            articleList.model=feedModel;
        }
    }


    ListView {      
        id: articleList;
        objectName:"articleList"
        x: 10
        y: 47
        model: feedModel
        width:292
        height:599
        delegate: Core.ArticleDelegate{
            id:listDelegate            
        }
        cacheBuffer: 100;
        boundsBehavior: Flickable.StopAtBounds
        snapMode: ListView.SnapToItem
        highlightRangeMode: ListView.NoHighlightRange
        highlight: Rectangle {
            id: selectionRectangle
            color: "#99F22C"
            smooth: true
            opacity:0.6
        }
        clip:true        
    }

    Core.Browser {
        id:browser
        x: 313
        y: 47
        height:650
        width:1050        
    }   

    Core.LoadingImage {
        id:loadingImage
        anchors.centerIn: parent;
        visible: false
    }


}
