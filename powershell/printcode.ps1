param (
	[string]$color,
	[string]$directoryPath
)
if ($directoryPath -eq ""){
	$directoryPath =  $args[1]
}
# $color_arr = @{"red"="DarkRed"
		# "Black"="Black"
		# "cyan"="DarkCyan"
		# "blue"="DarkBlue"
		# "Yellow"="Yellow"
		# }
$color_arr = @("DarkRed","DarkYellow","Yellow","Green","Blue","DarkCyan", ,"DarkMagenta	")
$count =0  # for rainbow
if ($directoryPath -eq "") {
	$directoryPath=Get-location
} 
$hexSequence = @(0xD, 0xA)
$sequenceBuffer = @()

Get-ChildItem -Path $directoryPath -Filter *.c | ForEach-Object {
	$file_path = Join-Path $directoryPath -ChildPath $_.Name 
	Get-Content -Path  $file_path | ForEach-Object {
		$line =$_
		foreach ( $byte in $line.ToCharArray()){
			switch ($color){
				"red"{
					Write-Host -NoNewline -ForegroundColor DarkRed $byte
				}
				"black"{
					Write-Host -NoNewline -ForegroundColor black $byte
				}
				"cyan"{
					Write-Host -NoNewline -ForegroundColor DarkCyan $byte
				}
				"blue"{
					Write-Host -NoNewline -ForegroundColor DarkBlue $byte
				}
				"Magenta"{
					Write-Host -NoNewline -ForegroundColor DarkMagenta $byte
				}
				"yellow"{
					Write-Host -NoNewline -ForegroundColor Yellow $byte
				}
				"rainbow"{
					$index = $count % $color_arr.Length
					# Write-Host $index
					# co@()
					Write-Host -NoNewline -ForegroundColor $color_arr[$index]  $byte
					
					 
					$count ++
					
				}
				default{
					Write-Host -NoNewline  $byte
				}

			}
			Start-Sleep -Milliseconds 10
		 }
		 Write-Host ""
	}
	# Write-Host $file_path
	# foreach ($byte in $file_content.ToCharArray()) {
		# $sequenceBuffer += $byte
		# if ($sequenceBuffer  -eq $hexSequence ){
			# Write-Host ""
			# $sequenceBuffer =@()
		# } else {
			# Write-Host -NoNewline $byte
		# }
		# Start-Sleep -Milliseconds 10
	# }
}

