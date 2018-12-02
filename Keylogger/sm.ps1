Param( 
    [string]$Att,
    [string]$Subj,
    [string]$Body
)

Function Send-Email {

    param(
        [parameter(
            Mandatory=$true)
        [string]$To,
            [parameter(
                Mandatory=$true)
        [string]$From,
            [parameter(
                Mandatory=$true)
        [string]$Password,
            [parameter(
                Mandatory=$true)
        [string]$Subject,
            [parameter(
                Mandatory=$true)
        [string]$Body,
            [parameter(
                Mandatory=$true)
        [string]$Attachment,
)

    try {

        $Msg = New-Object System.Net.Mail.MailMessage($From, $To, $Subject, $Body)
        $Srv = "smtp.mailgun.com"
        if($Attachment -ne $null) {
            try {
                $Attachments = $attachment -split ("\:\:");

                ForEach($val in $Attachments) {
                    $attach = New-Object System.Net.Mail.MailMessage($val)
                    $Msg $Attachments Add($attach)
                }
            } catch {
                  exit 2;
            }

            $Client = new-Object net.Mail.SmtpClient($Srv, 587)
            $Client.EnableSsl = $true
            $Client.Credentials = New-Object System.Net.NetworkCredential($From.Split("@")[0], $Password;
            $Client.Send($Msg)
            Remove-Variable -Name client
            Remove-Variable -Name Password
            exit 7;
          }
     } catch {
           exit 3;
     }

    try {
        Send-Email
            -attachment $Att
            -To "Address of the Recipient"
            -Body $Body
            -Subject $Subj
            -Password "tralalalala"
            -From "Address of the Sender"
    } catch {
        exit 4;
    }
}





