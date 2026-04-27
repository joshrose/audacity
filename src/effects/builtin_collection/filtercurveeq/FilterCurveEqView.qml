import QtQuick
import QtQuick.Controls
import Muse.Ui
import Muse.UiComponents
import Audacity.Effects
import Audacity.BuiltinEffects
import Audacity.BuiltinEffectsCollection

BuiltinEffectBase {
    id: root

    property string title: qsTrc("effects/filtercurveeq", "Filter Curve EQ")
    property bool isApplyAllowed: true

    width: boardRectangle.width
    implicitHeight: boardRectangle.height

    builtinEffectModel: FilterCurveEqViewModelFactory.createModel(root, root.instanceId)
    numNavigationPanels: 0
    property alias filterCurveEq: root.builtinEffectModel

    Rectangle {
        id: boardRectangle

        width: 720
        height: 420
        anchors.centerIn: parent

        radius: 8
        color: ui.theme.backgroundSecondaryColor
        border.color: ui.theme.strokeColor

        PolylinePlot {
            id: curve

            anchors.fill: parent
            anchors.margins: 16

            lineColor: ui.theme.accentColor
            lineWidth: 2

            pointRadius: 4.0
            pointOutlineColor: ui.theme.accentColor
            pointCentreColor: ui.theme.accentColor
            pointOutlineWidth: 2.0

            ghostPointRadius: 3.0
            ghostPointOutlineColor: ui.theme.accentColor

            points: filterCurveEq.curveModel.points
            defaultValue: filterCurveEq.curveModel.defaultValue

            xRangeFrom: 0.0
            xRangeTo: 1.0

            yRangeFrom: filterCurveEq.dbMin
            yRangeTo: filterCurveEq.dbMax
            yAxisInverse: true

            Component.onCompleted: {
                curve.init()
            }
        }
    }
}
