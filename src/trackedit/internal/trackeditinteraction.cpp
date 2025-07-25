#include "trackeditinteraction.h"

namespace au::trackedit {
TrackeditInteraction::TrackeditInteraction(std::unique_ptr<ITrackeditInteraction> interaction)
    : m_interaction(std::move(interaction))
{
}

muse::secs_t TrackeditInteraction::clipStartTime(const trackedit::ClipKey& clipKey) const
{
    return m_interaction->clipStartTime(clipKey);
}

muse::secs_t TrackeditInteraction::clipEndTime(const ClipKey& clipKey) const
{
    return m_interaction->clipEndTime(clipKey);
}

bool TrackeditInteraction::changeClipStartTime(const trackedit::ClipKey& clipKey, secs_t newStartTime, bool completed)
{
    return withPlaybackStop(&ITrackeditInteraction::changeClipStartTime, clipKey, newStartTime, completed);
}

muse::async::Channel<trackedit::ClipKey, secs_t /*newStartTime*/, bool /*completed*/> TrackeditInteraction::clipStartTimeChanged() const
{
    return m_interaction->clipStartTimeChanged();
}

bool TrackeditInteraction::trimTracksData(const std::vector<trackedit::TrackId>& tracksIds, secs_t begin, secs_t end)
{
    return withPlaybackStop(&ITrackeditInteraction::trimTracksData, tracksIds, begin, end);
}

bool TrackeditInteraction::silenceTracksData(const std::vector<trackedit::TrackId>& tracksIds, secs_t begin, secs_t end)
{
    return withPlaybackStop(&ITrackeditInteraction::silenceTracksData, tracksIds, begin, end);
}

bool TrackeditInteraction::changeTrackTitle(const trackedit::TrackId trackId, const muse::String& title)
{
    return m_interaction->changeTrackTitle(trackId, title);
}

bool TrackeditInteraction::changeClipTitle(const trackedit::ClipKey& clipKey, const muse::String& newTitle)
{
    return m_interaction->changeClipTitle(clipKey, newTitle);
}

bool TrackeditInteraction::changeClipPitch(const ClipKey& clipKey, int pitch)
{
    return m_interaction->changeClipPitch(clipKey, pitch);
}

bool TrackeditInteraction::resetClipPitch(const ClipKey& clipKey)
{
    return m_interaction->resetClipPitch(clipKey);
}

bool TrackeditInteraction::changeClipSpeed(const ClipKey& clipKey, double speed)
{
    return withPlaybackStop(&ITrackeditInteraction::changeClipSpeed, clipKey, speed);
}

bool TrackeditInteraction::resetClipSpeed(const ClipKey& clipKey)
{
    return withPlaybackStop(&ITrackeditInteraction::resetClipSpeed, clipKey);
}

bool TrackeditInteraction::changeClipColor(const ClipKey& clipKey, const std::string& color)
{
    return m_interaction->changeClipColor(clipKey, color);
}

bool TrackeditInteraction::changeTracksColor(const TrackIdList& tracksIds, const std::string& color)
{
    return m_interaction->changeTracksColor(tracksIds, color);
}

bool TrackeditInteraction::changeClipOptimizeForVoice(const ClipKey& clipKey, bool optimize)
{
    return withPlaybackStop(&ITrackeditInteraction::changeClipOptimizeForVoice, clipKey, optimize);
}

bool TrackeditInteraction::renderClipPitchAndSpeed(const ClipKey& clipKey)
{
    return withPlaybackStop(&ITrackeditInteraction::renderClipPitchAndSpeed, clipKey);
}

void TrackeditInteraction::clearClipboard()
{
    return m_interaction->clearClipboard();
}

muse::Ret TrackeditInteraction::pasteFromClipboard(secs_t begin, bool moveClips, bool moveAllTracks)
{
    return withPlaybackStop(&ITrackeditInteraction::pasteFromClipboard, begin, moveClips, moveAllTracks);
}

bool TrackeditInteraction::cutClipIntoClipboard(const ClipKey& clipKey)
{
    return withPlaybackStop(&ITrackeditInteraction::cutClipIntoClipboard, clipKey);
}

bool TrackeditInteraction::cutClipDataIntoClipboard(const TrackIdList& tracksIds, secs_t begin, secs_t end, bool moveClips)
{
    return withPlaybackStop(&ITrackeditInteraction::cutClipDataIntoClipboard, tracksIds, begin, end, moveClips);
}

bool TrackeditInteraction::copyClipIntoClipboard(const trackedit::ClipKey& clipKey)
{
    return m_interaction->copyClipIntoClipboard(clipKey);
}

bool TrackeditInteraction::copyNonContinuousTrackDataIntoClipboard(const TrackId trackId, const ClipKeyList& clipKeys, secs_t offset)
{
    return m_interaction->copyNonContinuousTrackDataIntoClipboard(trackId, clipKeys, offset);
}

bool TrackeditInteraction::copyContinuousTrackDataIntoClipboard(const TrackId trackId, secs_t begin, secs_t end)
{
    return m_interaction->copyContinuousTrackDataIntoClipboard(trackId, begin, end);
}

bool TrackeditInteraction::removeClip(const trackedit::ClipKey& clipKey)
{
    return withPlaybackStop(&ITrackeditInteraction::removeClip, clipKey);
}

bool TrackeditInteraction::removeClips(const ClipKeyList& clipKeyList, bool moveClips)
{
    return withPlaybackStop(&ITrackeditInteraction::removeClips, clipKeyList, moveClips);
}

bool TrackeditInteraction::removeTracksData(const TrackIdList& tracksIds, secs_t begin, secs_t end, bool moveClips)
{
    return withPlaybackStop(&ITrackeditInteraction::removeTracksData, tracksIds, begin, end, moveClips);
}

bool TrackeditInteraction::moveClips(secs_t timePositionOffset, int trackPositionOffset, bool completed, bool& clipsMovedToOtherTrack)
{
    return withPlaybackStop(&ITrackeditInteraction::moveClips,
                            timePositionOffset,
                            trackPositionOffset,
                            completed,
                            clipsMovedToOtherTrack);
}

bool TrackeditInteraction::splitTracksAt(const TrackIdList& tracksIds, std::vector<secs_t> pivots)
{
    return withPlaybackStop(&ITrackeditInteraction::splitTracksAt, tracksIds, pivots);
}

bool TrackeditInteraction::splitClipsAtSilences(const ClipKeyList& clipKeyList)
{
    return withPlaybackStop(&ITrackeditInteraction::splitClipsAtSilences, clipKeyList);
}

bool TrackeditInteraction::splitRangeSelectionAtSilences(const TrackIdList& tracksIds, secs_t begin, secs_t end)
{
    return withPlaybackStop(&ITrackeditInteraction::splitRangeSelectionAtSilences, tracksIds, begin, end);
}

bool TrackeditInteraction::splitRangeSelectionIntoNewTracks(const TrackIdList& tracksIds, secs_t begin, secs_t end)
{
    return withPlaybackStop(&ITrackeditInteraction::splitRangeSelectionIntoNewTracks, tracksIds, begin, end);
}

bool TrackeditInteraction::splitClipsIntoNewTracks(const ClipKeyList& clipKeyList)
{
    return withPlaybackStop(&ITrackeditInteraction::splitClipsIntoNewTracks, clipKeyList);
}

bool TrackeditInteraction::mergeSelectedOnTracks(const TrackIdList& tracksIds, secs_t begin, secs_t end)
{
    return withPlaybackStop(&ITrackeditInteraction::mergeSelectedOnTracks, tracksIds, begin, end);
}

bool TrackeditInteraction::duplicateSelectedOnTracks(const TrackIdList& tracksIds, secs_t begin, secs_t end)
{
    return withPlaybackStop(&ITrackeditInteraction::duplicateSelectedOnTracks, tracksIds, begin, end);
}

bool TrackeditInteraction::duplicateClip(const ClipKey& clipKey)
{
    return withPlaybackStop(&ITrackeditInteraction::duplicateClip, clipKey);
}

bool TrackeditInteraction::duplicateClips(const ClipKeyList& clipKeyList)
{
    return withPlaybackStop(&ITrackeditInteraction::duplicateClips, clipKeyList);
}

bool TrackeditInteraction::clipSplitCut(const ClipKey& clipKey)
{
    return withPlaybackStop(&ITrackeditInteraction::clipSplitCut, clipKey);
}

bool TrackeditInteraction::clipSplitDelete(const ClipKey& clipKey)
{
    return withPlaybackStop(&ITrackeditInteraction::clipSplitDelete, clipKey);
}

bool TrackeditInteraction::splitCutSelectedOnTracks(const TrackIdList tracksIds, secs_t begin, secs_t end)
{
    return withPlaybackStop(&ITrackeditInteraction::splitCutSelectedOnTracks, tracksIds, begin, end);
}

bool TrackeditInteraction::splitDeleteSelectedOnTracks(const TrackIdList tracksIds, secs_t begin, secs_t end)
{
    return withPlaybackStop(&ITrackeditInteraction::splitDeleteSelectedOnTracks, tracksIds, begin, end);
}

bool TrackeditInteraction::trimClipLeft(const ClipKey& clipKey, secs_t deltaSec, secs_t minClipDuration, bool completed, UndoPushType type)
{
    return withPlaybackStop(&ITrackeditInteraction::trimClipLeft, clipKey, deltaSec, minClipDuration, completed, type);
}

bool TrackeditInteraction::trimClipRight(const ClipKey& clipKey, secs_t deltaSec, secs_t minClipDuration, bool completed, UndoPushType type)
{
    return withPlaybackStop(&ITrackeditInteraction::trimClipRight, clipKey, deltaSec, minClipDuration, completed, type);
}

bool TrackeditInteraction::stretchClipLeft(const ClipKey& clipKey,
                                           secs_t deltaSec,
                                           secs_t minClipDuration,
                                           bool completed,
                                           UndoPushType type)
{
    return withPlaybackStop(&ITrackeditInteraction::stretchClipLeft, clipKey, deltaSec, minClipDuration, completed, type);
}

bool TrackeditInteraction::stretchClipRight(const ClipKey& clipKey,
                                            secs_t deltaSec,
                                            secs_t minClipDuration,
                                            bool completed,
                                            UndoPushType type)
{
    return withPlaybackStop(&ITrackeditInteraction::stretchClipRight,
                            clipKey,
                            deltaSec,
                            minClipDuration,
                            completed,
                            type);
}

muse::secs_t TrackeditInteraction::clipDuration(const trackedit::ClipKey& clipKey) const
{
    return m_interaction->clipDuration(clipKey);
}

std::optional<secs_t> TrackeditInteraction::getLeftmostClipStartTime(const ClipKeyList& clipKeys) const
{
    return m_interaction->getLeftmostClipStartTime(clipKeys);
}

bool TrackeditInteraction::newMonoTrack()
{
    return withPlaybackStop(&ITrackeditInteraction::newMonoTrack);
}

bool TrackeditInteraction::newStereoTrack()
{
    return withPlaybackStop(&ITrackeditInteraction::newStereoTrack);
}

bool TrackeditInteraction::newLabelTrack()
{
    return withPlaybackStop(&ITrackeditInteraction::newLabelTrack);
}

bool TrackeditInteraction::deleteTracks(const TrackIdList& trackIds)
{
    return withPlaybackStop(&ITrackeditInteraction::deleteTracks, trackIds);
}

bool TrackeditInteraction::duplicateTracks(const TrackIdList& trackIds)
{
    return withPlaybackStop(&ITrackeditInteraction::duplicateTracks, trackIds);
}

void TrackeditInteraction::moveTracks(const TrackIdList& trackIds, const TrackMoveDirection direction)
{
    return m_interaction->moveTracks(trackIds, direction);
}

void TrackeditInteraction::moveTracksTo(const TrackIdList& trackIds, int to)
{
    return m_interaction->moveTracksTo(trackIds, to);
}

bool TrackeditInteraction::undo()
{
    return withPlaybackStop(&ITrackeditInteraction::undo);
}

bool TrackeditInteraction::canUndo()
{
    return m_interaction->canUndo();
}

bool TrackeditInteraction::redo()
{
    return withPlaybackStop(&ITrackeditInteraction::redo);
}

bool TrackeditInteraction::canRedo()
{
    return m_interaction->canRedo();
}

bool TrackeditInteraction::undoRedoToIndex(size_t index)
{
    return m_interaction->undoRedoToIndex(index);
}

bool TrackeditInteraction::insertSilence(const TrackIdList& trackIds, secs_t begin, secs_t end, secs_t duration)
{
    return withPlaybackStop(&ITrackeditInteraction::insertSilence, trackIds, begin, end, duration);
}

bool TrackeditInteraction::toggleStretchToMatchProjectTempo(const ClipKey& clipKey)
{
    return withPlaybackStop(&ITrackeditInteraction::toggleStretchToMatchProjectTempo, clipKey);
}

int64_t TrackeditInteraction::clipGroupId(const ClipKey& clipKey) const
{
    return m_interaction->clipGroupId(clipKey);
}

void TrackeditInteraction::setClipGroupId(const ClipKey& clipKey, int64_t id)
{
    return m_interaction->setClipGroupId(clipKey, id);
}

void TrackeditInteraction::groupClips(const ClipKeyList& clipKeyList)
{
    return m_interaction->groupClips(clipKeyList);
}

void TrackeditInteraction::ungroupClips(const ClipKeyList& clipKeyList)
{
    return m_interaction->ungroupClips(clipKeyList);
}

ClipKeyList TrackeditInteraction::clipsInGroup(int64_t id) const
{
    return m_interaction->clipsInGroup(id);
}

bool TrackeditInteraction::changeTracksFormat(const TrackIdList& tracksIds, trackedit::TrackFormat format)
{
    return withProgress([&, this]() {
        return withPlaybackStop(&ITrackeditInteraction::changeTracksFormat, tracksIds, format);
    });
}

muse::ProgressPtr TrackeditInteraction::progress() const
{
    return m_interaction->progress();
}
}
