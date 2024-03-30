namespace KeyAuth
{
    public partial class Main : global::System.Windows.Forms.Form
    {
        protected override void Dispose(bool disposing)
        {
            bool flag = disposing && this.components != null;
            if (flag)
            {
                this.components.Dispose();
            }
            base.Dispose(disposing);
        }
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.siticoneDragControl1 = new Siticone.UI.WinForms.SiticoneDragControl(this.components);
            this.siticoneControlBox1 = new Siticone.UI.WinForms.SiticoneControlBox();
            this.label1 = new System.Windows.Forms.Label();
            this.sendmsg = new Siticone.UI.WinForms.SiticoneRoundedButton();
            this.siticoneShadowForm = new Siticone.UI.WinForms.SiticoneShadowForm(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.siticoneCirclePictureBox1 = new Siticone.Desktop.UI.WinForms.SiticoneCirclePictureBox();
            this.expiry = new Siticone.UI.WinForms.SiticoneLabel();
            ((System.ComponentModel.ISupportInitialize)(this.siticoneCirclePictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // siticoneDragControl1
            // 
            this.siticoneDragControl1.TargetControl = this;
            // 
            // siticoneControlBox1
            // 
            this.siticoneControlBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.siticoneControlBox1.BorderRadius = 10;
            this.siticoneControlBox1.FillColor = System.Drawing.Color.Transparent;
            this.siticoneControlBox1.HoveredState.FillColor = System.Drawing.Color.Transparent;
            this.siticoneControlBox1.HoveredState.IconColor = System.Drawing.Color.White;
            this.siticoneControlBox1.HoveredState.Parent = this.siticoneControlBox1;
            this.siticoneControlBox1.IconColor = System.Drawing.Color.White;
            this.siticoneControlBox1.Location = new System.Drawing.Point(403, 4);
            this.siticoneControlBox1.Name = "siticoneControlBox1";
            this.siticoneControlBox1.ShadowDecoration.Parent = this.siticoneControlBox1;
            this.siticoneControlBox1.Size = new System.Drawing.Size(45, 29);
            this.siticoneControlBox1.TabIndex = 1;
            this.siticoneControlBox1.Click += new System.EventHandler(this.siticoneControlBox1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI Light", 10F);
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(-1, 136);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 19);
            this.label1.TabIndex = 22;
            // 
            // sendmsg
            // 
            this.sendmsg.BorderColor = System.Drawing.Color.White;
            this.sendmsg.BorderThickness = 1;
            this.sendmsg.CheckedState.Parent = this.sendmsg;
            this.sendmsg.CustomImages.Parent = this.sendmsg;
            this.sendmsg.FillColor = System.Drawing.Color.Transparent;
            this.sendmsg.Font = new System.Drawing.Font("Times New Roman", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.sendmsg.ForeColor = System.Drawing.Color.White;
            this.sendmsg.HoveredState.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(213)))), ((int)(((byte)(218)))), ((int)(((byte)(223)))));
            this.sendmsg.HoveredState.Parent = this.sendmsg;
            this.sendmsg.Location = new System.Drawing.Point(146, 267);
            this.sendmsg.Name = "sendmsg";
            this.sendmsg.ShadowDecoration.Parent = this.sendmsg;
            this.sendmsg.Size = new System.Drawing.Size(151, 27);
            this.sendmsg.TabIndex = 42;
            this.sendmsg.Text = "Inject";
            this.sendmsg.Click += new System.EventHandler(this.sendmsg_Click);
            // 
            // siticoneCirclePictureBox1
            // 
            this.siticoneCirclePictureBox1.BackColor = System.Drawing.Color.Transparent;
            this.siticoneCirclePictureBox1.FillColor = System.Drawing.Color.Transparent;
            this.siticoneCirclePictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("siticoneCirclePictureBox1.Image")));
            this.siticoneCirclePictureBox1.ImageRotate = 0F;
            this.siticoneCirclePictureBox1.Location = new System.Drawing.Point(160, 63);
            this.siticoneCirclePictureBox1.Name = "siticoneCirclePictureBox1";
            this.siticoneCirclePictureBox1.ShadowDecoration.Mode = Siticone.Desktop.UI.WinForms.Enums.ShadowMode.Circle;
            this.siticoneCirclePictureBox1.Size = new System.Drawing.Size(128, 112);
            this.siticoneCirclePictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.siticoneCirclePictureBox1.TabIndex = 43;
            this.siticoneCirclePictureBox1.TabStop = false;
            // 
            // expiry
            // 
            this.expiry.BackColor = System.Drawing.Color.Transparent;
            this.expiry.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.expiry.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.expiry.Location = new System.Drawing.Point(11, 475);
            this.expiry.Margin = new System.Windows.Forms.Padding(2);
            this.expiry.Name = "expiry";
            this.expiry.Size = new System.Drawing.Size(3, 2);
            this.expiry.TabIndex = 38;
            this.expiry.Text = null;
            this.expiry.Click += new System.EventHandler(this.expiry_Click);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoValidate = System.Windows.Forms.AutoValidate.Disable;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(452, 502);
            this.Controls.Add(this.siticoneCirclePictureBox1);
            this.Controls.Add(this.sendmsg);
            this.Controls.Add(this.expiry);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.siticoneControlBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Loader";
            this.TransparencyKey = System.Drawing.Color.Maroon;
            this.Load += new System.EventHandler(this.Main_Load);
            ((System.ComponentModel.ISupportInitialize)(this.siticoneCirclePictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        // Token: 0x04000001 RID: 1
        private global::System.ComponentModel.IContainer components = null;

        // Token: 0x04000002 RID: 2
        private global::Siticone.UI.WinForms.SiticoneDragControl siticoneDragControl1;

        // Token: 0x04000004 RID: 4
        private global::Siticone.UI.WinForms.SiticoneControlBox siticoneControlBox1;

        // Token: 0x0400000A RID: 10
        private global::System.Windows.Forms.Label label1;
        private Siticone.UI.WinForms.SiticoneShadowForm siticoneShadowForm;
        private Siticone.UI.WinForms.SiticoneRoundedButton sendmsg;
        private System.Windows.Forms.Timer timer1;
        private Siticone.Desktop.UI.WinForms.SiticoneCirclePictureBox siticoneCirclePictureBox1;
        private Siticone.UI.WinForms.SiticoneLabel expiry;
    }
}
