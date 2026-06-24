using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace App
{
    public class Delivery
    {
        public int Id { get; set; }
        public string Package { get; set; }
        public string Driver { get; set; }
        public string DeliveryType { get; set; }
        public string Priority { get; set; }
        public string Status { get; set; }
        public bool Assigned { get; set; }
    }

    public class DeliveryApp : Form
    {
        private int nextId = 1;
        private readonly List<Delivery> deliveries = new List<Delivery>();

        private TextBox packageEntry;
        private TextBox driverEntry;

        private RadioButton deliveryTypeStandard;
        private RadioButton deliveryTypeExpress;
        private RadioButton deliveryTypeSameDay;

        private RadioButton priorityLow;
        private RadioButton priorityMedium;
        private RadioButton priorityHigh;

        private Button addButton;
        private Button clearButton;
        private Button dispatchButton;
        private Button assignDriverButton;

        private DataGridView deliveryGrid;
        private TextBox countValueBox;

        public DeliveryApp()
        {
            InitializeComponent();
            CheckAddButtonState();
            UpdateActionButtonsState();
        }

        private void InitializeComponent()
        {
            Text = "Система регистрации доставок";
            Size = new Size(850, 650);
            StartPosition = FormStartPosition.CenterScreen;
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MaximizeBox = false;

            var mainPanel = new Panel
            {
                Dock = DockStyle.Fill,
                Padding = new Padding(10)
            };

            var inputGroup = new GroupBox
            {
                Text = "Информация о доставке",
                Dock = DockStyle.Top,
                Height = 235,
                Padding = new Padding(10),
                BackColor = Color.WhiteSmoke
            };

            var inputTable = new TableLayoutPanel
            {
                Dock = DockStyle.Fill,
                ColumnCount = 2,
                RowCount = 5,
                Padding = new Padding(5)
            };

            inputTable.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 120));
            inputTable.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));

            for (int i = 0; i < 5; i++)
                inputTable.RowStyles.Add(new RowStyle(SizeType.Absolute, 35));

            var lblPackage = new Label
            {
                Text = "Package:",
                TextAlign = ContentAlignment.MiddleRight,
                Dock = DockStyle.Fill
            };

            packageEntry = new TextBox
            {
                Width = 300,
                Anchor = AnchorStyles.Left,
                BackColor = Color.LightYellow,
                TextAlign = HorizontalAlignment.Right
            };
            packageEntry.TextChanged += OnInputChanged;

            var lblDriver = new Label
            {
                Text = "Driver:",
                TextAlign = ContentAlignment.MiddleRight,
                Dock = DockStyle.Fill
            };

            driverEntry = new TextBox
            {
                Width = 300,
                Anchor = AnchorStyles.Left,
                BackColor = Color.LightCyan,
                TextAlign = HorizontalAlignment.Right
            };
            driverEntry.TextChanged += OnInputChanged;

            var lblDeliveryType = new Label
            {
                Text = "Delivery Type:",
                TextAlign = ContentAlignment.MiddleRight,
                Dock = DockStyle.Fill
            };

            var deliveryPanel = new Panel
            {
                Height = 30,
                Dock = DockStyle.Fill,
                BackColor = Color.Honeydew
            };

            deliveryTypeStandard = new RadioButton
            {
                Text = "Standard",
                Location = new Point(5, 5),
                AutoSize = true,
                BackColor = Color.Honeydew
            };
            deliveryTypeStandard.CheckedChanged += OnInputChanged;

            deliveryTypeExpress = new RadioButton
            {
                Text = "Express",
                Location = new Point(85, 5),
                AutoSize = true,
                BackColor = Color.Honeydew
            };
            deliveryTypeExpress.CheckedChanged += OnInputChanged;

            deliveryTypeSameDay = new RadioButton
            {
                Text = "Same-day",
                Location = new Point(165, 5),
                AutoSize = true,
                BackColor = Color.Honeydew
            };
            deliveryTypeSameDay.CheckedChanged += OnInputChanged;

            deliveryPanel.Controls.Add(deliveryTypeStandard);
            deliveryPanel.Controls.Add(deliveryTypeExpress);
            deliveryPanel.Controls.Add(deliveryTypeSameDay);

            var lblPriority = new Label
            {
                Text = "Priority:",
                TextAlign = ContentAlignment.MiddleRight,
                Dock = DockStyle.Fill
            };

            var priorityPanel = new Panel
            {
                Height = 30,
                Dock = DockStyle.Fill,
                BackColor = Color.MistyRose
            };

            priorityLow = new RadioButton
            {
                Text = "Low",
                Location = new Point(5, 5),
                AutoSize = true,
                BackColor = Color.MistyRose
            };
            priorityLow.CheckedChanged += OnInputChanged;

            priorityMedium = new RadioButton
            {
                Text = "Medium",
                Location = new Point(55, 5),
                AutoSize = true,
                BackColor = Color.MistyRose
            };
            priorityMedium.CheckedChanged += OnInputChanged;

            priorityHigh = new RadioButton
            {
                Text = "High",
                Location = new Point(125, 5),
                AutoSize = true,
                BackColor = Color.MistyRose
            };
            priorityHigh.CheckedChanged += OnInputChanged;

            priorityPanel.Controls.Add(priorityLow);
            priorityPanel.Controls.Add(priorityMedium);
            priorityPanel.Controls.Add(priorityHigh);

            var buttonsPanel = new Panel
            {
                Height = 40,
                Dock = DockStyle.Fill,
                BackColor = Color.WhiteSmoke
            };

            addButton = new Button
            {
                Text = "➕ Add",
                Width = 120,
                Height = 30,
                Location = new Point(5, 5)
            };
            addButton.Click += OnAddClick;

            clearButton = new Button
            {
                Text = "🧹 Clear Form",
                Width = 120,
                Height = 30,
                Location = new Point(135, 5)
            };
            clearButton.Click += OnClearClick;

            buttonsPanel.Controls.Add(addButton);
            buttonsPanel.Controls.Add(clearButton);

            inputTable.Controls.Add(lblPackage, 0, 0);
            inputTable.Controls.Add(packageEntry, 1, 0);

            inputTable.Controls.Add(lblDriver, 0, 1);
            inputTable.Controls.Add(driverEntry, 1, 1);

            inputTable.Controls.Add(lblDeliveryType, 0, 2);
            inputTable.Controls.Add(deliveryPanel, 1, 2);

            inputTable.Controls.Add(lblPriority, 0, 3);
            inputTable.Controls.Add(priorityPanel, 1, 3);

            inputTable.Controls.Add(buttonsPanel, 1, 4);

            inputGroup.Controls.Add(inputTable);

            var tableGroup = new GroupBox
            {
                Text = "Зарегистрированные доставки",
                Dock = DockStyle.Fill,
                Padding = new Padding(10),
                BackColor = Color.White
            };

            var tablePanel = new Panel
            {
                Dock = DockStyle.Fill
            };

            deliveryGrid = new DataGridView
            {
                Dock = DockStyle.Top,
                Height = 280,
                AllowUserToAddRows = false,
                AllowUserToDeleteRows = false,
                ReadOnly = true,
                RowHeadersVisible = false,
                SelectionMode = DataGridViewSelectionMode.FullRowSelect,
                MultiSelect = false,
                AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill,
                BackgroundColor = Color.AliceBlue
            };

            deliveryGrid.Columns.Add("ID", "ID");
            deliveryGrid.Columns.Add("Package", "Package");
            deliveryGrid.Columns.Add("Driver", "Driver");
            deliveryGrid.Columns.Add("DeliveryType", "Delivery Type");
            deliveryGrid.Columns.Add("Priority", "Priority");
            deliveryGrid.Columns.Add("Assigned", "Assigned");
            deliveryGrid.Columns.Add("Status", "Status");

            deliveryGrid.DefaultCellStyle.SelectionBackColor = Color.White;
            deliveryGrid.DefaultCellStyle.SelectionForeColor = Color.Black;

            deliveryGrid.RowsDefaultCellStyle.SelectionBackColor = Color.White;
            deliveryGrid.RowsDefaultCellStyle.SelectionForeColor = Color.Black;

            deliveryGrid.AlternatingRowsDefaultCellStyle.SelectionBackColor = Color.White;
            deliveryGrid.AlternatingRowsDefaultCellStyle.SelectionForeColor = Color.Black;

            deliveryGrid.Columns[0].Width = 50;
            deliveryGrid.Columns[5].Width = 90;
            deliveryGrid.Columns[6].Width = 90;

            deliveryGrid.SelectionChanged += DeliveryGrid_SelectionChanged;

            var actionPanel = new Panel
            {
                Dock = DockStyle.Top,
                Height = 50,
                BackColor = Color.Lavender
            };

            dispatchButton = new Button
            {
                Text = "🚚 Dispatch Delivery",
                Width = 170,
                Height = 32,
                Location = new Point(5, 10),
                Enabled = false
            };
            dispatchButton.Click += OnDispatchClick;

            assignDriverButton = new Button
            {
                Text = "👤 Assign Driver",
                Width = 170,
                Height = 32,
                Location = new Point(185, 10),
                Enabled = false
            };
            assignDriverButton.Click += OnAssignDriverClick;

            actionPanel.Controls.Add(dispatchButton);
            actionPanel.Controls.Add(assignDriverButton);

            tablePanel.Controls.Add(actionPanel);
            tablePanel.Controls.Add(deliveryGrid);

            tableGroup.Controls.Add(tablePanel);

            mainPanel.Controls.Add(tableGroup);
            mainPanel.Controls.Add(inputGroup);

            countValueBox = new TextBox
            {
                Text = "0",
                Location = new Point(10, 585),
                Width = 50,
                ReadOnly = true,
                BorderStyle = BorderStyle.None,
                BackColor = Color.LightGoldenrodYellow,
                ForeColor = Color.Blue,
                TextAlign = HorizontalAlignment.Right
            };

            Controls.Add(countValueBox);
            Controls.Add(mainPanel);
        }

        private string GetSelectedDeliveryType()
        {
            if (deliveryTypeStandard.Checked) return "Standard";
            if (deliveryTypeExpress.Checked) return "Express";
            if (deliveryTypeSameDay.Checked) return "Same-day";
            return string.Empty;
        }

        private string GetSelectedPriority()
        {
            if (priorityLow.Checked) return "Low (+)";
            if (priorityMedium.Checked) return "Medium (+)";
            if (priorityHigh.Checked) return "High (+)";
            return string.Empty;
        }

        private void OnInputChanged(object sender, EventArgs e)
        {
            CheckAddButtonState();
        }

        private void CheckAddButtonState()
        {
            string package = packageEntry.Text.Trim();
            string deliveryType = GetSelectedDeliveryType();
            string priority = GetSelectedPriority();

            addButton.Enabled =
                !string.IsNullOrWhiteSpace(package) &&
                !string.IsNullOrWhiteSpace(deliveryType) &&
                !string.IsNullOrWhiteSpace(priority);
        }

        private void OnAddClick(object sender, EventArgs e)
        {
            string package = packageEntry.Text.Trim();
            string driver = driverEntry.Text.Trim();
            string deliveryType = GetSelectedDeliveryType();
            string priority = GetSelectedPriority();

            if (string.IsNullOrWhiteSpace(package) ||
                string.IsNullOrWhiteSpace(deliveryType) ||
                string.IsNullOrWhiteSpace(priority))
            {
                return;
            }

            var newDelivery = new Delivery
            {
                Id = nextId,
                Package = package,
                Driver = driver,
                DeliveryType = deliveryType,
                Priority = priority,
                Assigned = false,
                Status = "New"
            };

            deliveries.Add(newDelivery);

            int rowIndex = deliveryGrid.Rows.Add(
                newDelivery.Id,
                newDelivery.Package,
                newDelivery.Driver,
                newDelivery.DeliveryType,
                newDelivery.Priority,
                newDelivery.Assigned,
                newDelivery.Status
            );

            PaintAssignedCell(rowIndex);

            nextId++;
            ClearForm();
            countValueBox.Text = deliveries.Count.ToString();
            UpdateActionButtonsState();
        }

        private void OnClearClick(object sender, EventArgs e)
        {
            ClearForm();
        }

        private void OnDispatchClick(object sender, EventArgs e)
        {
            Delivery selectedDelivery = GetSelectedDelivery();
            DataGridViewRow selectedRow = GetSelectedRow();

            if (selectedDelivery == null || selectedRow == null)
                return;

            if (selectedDelivery.Status == "Dispatched")
            {
                UpdateActionButtonsState();
                return;
            }

            selectedDelivery.Status = "Dispatched";
            selectedRow.Cells["Status"].Value = "Dispatched";

            UpdateActionButtonsState();
        }

        private void OnAssignDriverClick(object sender, EventArgs e)
        {
            Delivery selectedDelivery = GetSelectedDelivery();
            DataGridViewRow selectedRow = GetSelectedRow();

            if (selectedDelivery == null || selectedRow == null)
                return;

            selectedDelivery.Assigned = true;
            selectedRow.Cells["Assigned"].Value = true;

            PaintAssignedCell(selectedRow.Index);

            UpdateActionButtonsState();
        }

        private void PaintAssignedCell(int rowIndex)
        {
            DataGridViewRow row = deliveryGrid.Rows[rowIndex];

            if (Convert.ToBoolean(row.Cells["Assigned"].Value))
            {
                row.Cells["Assigned"].Style.BackColor = Color.Lime;
                row.Cells["Assigned"].Style.SelectionBackColor = Color.Lime;
                row.Cells["Assigned"].Style.ForeColor = Color.Black;
                row.Cells["Assigned"].Style.SelectionForeColor = Color.Black;
                row.Cells["Assigned"].Style.Font =
                    new Font(deliveryGrid.Font, FontStyle.Bold);
            }
            else
            {
                row.Cells["Assigned"].Style.BackColor = Color.White;
                row.Cells["Assigned"].Style.SelectionBackColor = Color.White;
                row.Cells["Assigned"].Style.ForeColor = Color.Black;
                row.Cells["Assigned"].Style.SelectionForeColor = Color.Black;
            }
        }

        private void DeliveryGrid_SelectionChanged(object sender, EventArgs e)
        {
            UpdateActionButtonsState();
        }

        private void UpdateActionButtonsState()
        {
            bool hasSelection = deliveryGrid.SelectedRows.Count > 0;

            assignDriverButton.Enabled = hasSelection;

            if (!hasSelection)
            {
                dispatchButton.Enabled = false;
                return;
            }

            Delivery selectedDelivery = GetSelectedDelivery();

            dispatchButton.Enabled =
                selectedDelivery != null &&
                selectedDelivery.Status != "Dispatched";
        }

        private Delivery GetSelectedDelivery()
        {
            if (deliveryGrid.SelectedRows.Count == 0)
                return null;

            DataGridViewRow selectedRow = deliveryGrid.SelectedRows[0];
            int id = Convert.ToInt32(selectedRow.Cells["ID"].Value);

            foreach (var delivery in deliveries)
            {
                if (delivery.Id == id)
                    return delivery;
            }

            return null;
        }

        private DataGridViewRow GetSelectedRow()
        {
            if (deliveryGrid.SelectedRows.Count == 0)
                return null;

            return deliveryGrid.SelectedRows[0];
        }

        private void ClearForm()
        {
            packageEntry.Text = "";
            driverEntry.Text = "";

            deliveryTypeStandard.Checked = false;
            deliveryTypeExpress.Checked = false;
            deliveryTypeSameDay.Checked = false;

            priorityLow.Checked = false;
            priorityMedium.Checked = false;
            priorityHigh.Checked = false;

            CheckAddButtonState();
        }

        [STAThread]
        public static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new DeliveryApp());
        }
    }
}