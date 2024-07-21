import QtQuick

Window {

    readonly property var fonts: Qt.fontFamilies()

    property string name: qsTr("xxx")
    onNameChanged: {
        content.text = name;
    }

    onTitleChanged: {
        console.log("fuck you!!!")
    }
    id:rootId
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        id:redRectId
        color: "red"
        width: 50
        height: width * 1.5
    }

    Rectangle{
        id:blueRectId
        color: "blue"
        width: 100
        height: 100

        anchors.bottom: parent.bottom

        MouseArea{
            anchors.fill: parent
            onClicked: {
                redRectId.width = redRectId.width + 10
                console.log("....!!!")
            }
        }
    }

    Rectangle{
        id:greenRectId
        color: "green"
        width: 100
        height: 100

        anchors.bottom: parent.bottom
        anchors.left:blueRectId.right

        MouseArea{
            anchors.fill: parent
            onClicked: {
                //redRectId.height = redRectId.width + 10
                redRectId.height = Qt.binding(function(){
                    return redRectId.width * 2.5
                })
            }
        }
    }

    Rectangle{
        id:yellowRectid
        width: 200;
        height: 200;
        color: "yellow"

        anchors.centerIn: parent

        Text {
            anchors.centerIn: parent
            id: content
            color: Qt.rgba(100, 0, 0, 1)
            text: "name"
            font.pointSize: 20
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {
                //Qt.quit()

                //content.text = Qt.md5("呵呵哒！")

                for(var i = 0; i < fonts.length; i++){
                    console.log("[" + i + "]" + fonts[i])
                }


                // Qt.openUrlExternally("http://baidu.com")
                // Qt.openUrlExternally("file:///C:/Users/tang/Desktop/2022.5.26胡照片/5.26/DSC_0411.JPG")

                //console.log(Qt.platform.os)

                name = qsTr("董路帆")

                rootId.title = "qqq"
            }
        }

    }

}
