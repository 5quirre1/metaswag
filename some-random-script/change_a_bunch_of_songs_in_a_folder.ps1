$artist = "artist_name"
$album = "album_name"
$year = 2000
$cover = "cover.jpg"

$trackTitles = @(
    "track_1_title"
    #add more if more
)

$files = Get-ChildItem *.m4a | Sort-Object LastWriteTime

for ($i = 0; $i -lt $files.Count; $i++) {
    $file = $files[$i]
    $trackNumber = $i + 1
    $title = $trackTitles[$i]
    $newName = "{0:D2} - {1}.m4a" -f $trackNumber, $title #or change to mp3
    if ($file.Name -ne $newName) {
        Rename-Item $file.FullName -NewName $newName -Force
    }
    metaswag --file $newName --title $title --artist $artist --album $album --year $year --track $trackNumber --cover $cover
}
